using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Design;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;

/*
---Entity Framework (EF) - continuation ---
   https://www.youtube.com/watch?v=o9XoiPPP2Lw

a0) An entity in Entity Framework is a class 
    that maps to a database table. 
    This class must be included as a DbSet<TEntity> type 
    property in the DbContext class. 
    EF API maps each entity to a table and each property of an 
    entity to a column in the database. 
    e.g.: Student , and Grade are entities.

a) Change tracker = mechanism used by EF to define changes done in the objects to be pesisted in the db.
   I will compare the version initial of the object (persisted in the db) X versus the actual content of
   this object, in memory (c# code)
   (*) It trackes changes in OBJECTS THAT IT ALREADY KNOWS !!!
       change tracker has a State -> to inform details about the tracking object
       e.g.: tracking state of newDish created object in c#
             var state = dbContext.Entry(newDish).State

b) EF tracking objects - State Machine
   -creating a new object -> var newDish = new Dish { Title = "Foo", Notes = "Bar" };

    s1) initial state = Detached
        -EF has no idea who is this object - it did not
         come from the database !!!

    s2) state = Added
        -when new object added to the dbContext
         EF starts tracking it (but not saved in DB yet!)
         (needs sth like SaveChangesAsync to persist object in the DB) 
        -e.g.:
         dbContext.Dishes.Add(newDish);
         (*) add - just add the object to EF change tracker !

    s3) state = Unchanged
        -After the command SaveChangesAsync()
         the object in memory is saved to the DB.
        -So, there is no differences between the
         object in memory (being tracked by EF) and
         its content in the DB - so, unchanged is its state 
    
    s3) state = Modified
        -when we change the content of a tracked object
        -EF knows that there are outstanding changes
         that must be updated/persisted in the DB
        -e.g.: newDish.Notes = "Baz";
         (*) state = Unchanged  again, after a SaveChangesAsync()

    s4) state = Deleted
        -after we delete the in memory obj. under
         EF control.
        -e.g.: dbContext.Dishes.Remove(newDish);

    s5) state = Detached (from Delete state)
        -after execution of a save to database
         [SaveChangesAsync()], the obj. was removed
         from the DB, and the in memory obj. that was being
         tracked by EF goes to the state Detached again
         (not known/tracked by EF anymore)

    --- Details on how EF performs the tracking changes ---

0) the tracking is always done for a/each dbContext, individually

1) OriginalValues property:
   -used by EF for changes detection
   -keeps values as they are in the DB
   -EF always keep in this property:
    ..the original value that came from the DB or
    ..has been written to the DB previously
   -When a Save changes is called (SaveChangesAsync()), EF simply compares
    OriginalValues property versus the actual value of the entity (in memory c# obj)
    to detect which changes were done (to persist them into the DB).
   -It will check the differences for each entity fields what were the original values versus
    the actual values (in memory) - to decide which fields to persist
   -Based on the differeces (modified fields) EF can build the correct UPDATE
    query, adding only the modified fields, for instance.
        e.g.:
        var entry = dbContext.Entry(newDish);
        var originalValue = entry.OriginalValues[nameof(Dish.Notes)].ToString();

2) VIP: Execute queries will return values FROM THE ENTITY in memory
   (NOT GOING TO THE DB), if the entity was modified; otherwise,
   it will go to the DB to get the results.

3) dbContexts -> ine EF, we have a CHANGE TRACKING BY dbContext !!!
   -isolate the changes
   -and always update its own changes to the db
   -I can have several dbContexts in my application (if necessary)
    to cover specific situations

4) Make entity Detached 
   -force EF to forget about an object/entity being tracked
   -we change its state to Detached
    e.g.:
    dbContext.Entry(newDish).State = EntityState.Detached;

    (*) it is possible to change to other status also !!!
        but, be careful!

5) Update + Detached (unknown) obj., EF:
   -add it to the change tracker
   -then, during the Save, it will override all
    fields in the database (as for untracked objs
    it does not know which fields changed, it saves all)
    e.g.:
    dbContext.Dishes.Update(newDish);
    await dbContext.SaveChangesAsync();
    (*) This is useful with Web APIs, where we get the objs
        via HTTP (untracked), then, we save them in the DB.

6) Reading data from DB - tracking and not tracking data via EF
   -Normally, ALL data/entries/items read from DB will be tracked
    via EF - going to the state Unchanged.
    e.g.:
    // state below = Unchanged
    var dishes = await dbContext.Dishes.ToArrayAsync();
    var state = dbContext.Entry(dishes[0]).State;
    (*) this can be heavy, and a hit in performance
        but IS NECESSARY to start the tracking process

   -Not tracking data from DB:
    ..used when we just want to read the data
      (to generate a reporte, for instance) and we
      will not change it in any way.
    ..much better performance in this case to load data
    e.g.:
        // state below = Detached
        var dishesNoTrck = await dbContext.Dishes.AsNoTracking().ToArrayAsync();
        var stateNoTrck = dbContext.Entry(dishesNoTrck[0]).State;

 7)  Raw SQL queries:
     -The prefered to generate queries should
      be always FIRST via LINQ

     -sometimes we need to use them, as for more complex
      queries, or some specific feature of the underlined
      DB that might not available via Linq; e.g.:
      "with clause" - not available with Linq.

    -even with raw queries, we are still in EF world control,
     menaing that the object/entities that we get back
     from the DB (result of the query) will be tracked
     for changes normally by EF.
     e.g.:
        var dishes = await dbContext.Dishes
            .FromSqlRaw("SELECT * from Dishes")
            .ToArrayAsync();
    
        //state = Unchanged !!! so, still managed by EF's changes tracker
        var state = dbContext.Entry(dishes[0]).State;
        (*) the state=Unchanged -> showing that
            EF is tracking the returned entities
            from the DB.

    -Raw Sql + passing PARAMETERS
     ..use FromSqlInterpolated -> $"...{parm}"
     e.g.:
        var filter = "B%"; // parameter
        var dishes2 = await dbContext.Dishes
            .FromSqlInterpolated($"SELECT * from Dishes WHERE Notes LIKE {filter}")
            .ToArrayAsync();
      (*) this is the query generated:
          SELECT * from Dishes WHERE Notes LIKE @p0
          ->This is safe - it uses the @p0 in the query
            and not the parameter as string (which could
            be vulnerable to SQL INJECTION)
        
    -VIP: NEVER ADD PARAMETERS CONTENT manually
          in the raw query -> the command will
          be vulnerable to SQL INJECTION
          ALWAYS USE INTERPOLATION to provide
          parameters.
          For instance, if parameters of the query
          are given by users, they might add
          crase stuff, as below, to drop tables, erase table content
          intentionally or by mistake
        e.g.:
        //BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD
        //BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD
        //Example of query vulnerable to SQL INJECTION
        >>>>>>>>> var filter3 = "B%; DROP TABLE xyz";
        var dishes3 = await dbContext.Dishes
            .FromSqlRaw("SELECT * from Dishes WHERE Notes LIKE '"+filter3+"'")
            .ToArrayAsync();
        //BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD
        (*) And c# will generate & execute the "dangerous
            query" with the parameters provided; e.g:
            SELECT * from Dishes WHERE Notes LIKE 'B%; DROP TABLE xyz'

    -Raw Queries + WRITING statements (delete, update, etc)
     ..use: ExecuteSqlRawAsync
     ..e.g:
       await dbContext.Database.ExecuteSqlRawAsync
        ("DELETE FROM Dishes WHERE Id <= 20");

    //--- transactions ---

    -set of queries must exectute atomicaly - all or nothing
    -EF, steps to build a transaction:
        a) add the whole block in a try/catch block
        b) start the transacation before the try/catch block
        c) commit the transaction in the try block
        e.g.:
    using var transaction = await dbContext.Database.BeginTransactionAsync();
    try
    {
        // list of SQL command coumpound the transaction
        ...

        //end the transaction
        transaction.Commit();
    }
    catch (Microsoft.Data.SqlClient.SqlException e)
    {
        Console.WriteLine($"ERROR - exception info={e.Message}");
    }
    (*) if an exception occurs, an automatic rollback 
        will occurs (due to the initial using), as we
        have finished the try/catch block without
        doing a commit !

    //---LINQ queries - conversion to EXPRESSION TREES
    Conversion 
    ->from:
    var dishes = await dbContext.Dishes
            .Where(d => d.Title.StartsWith("F"))
            .ToArrayAsync();
    ->to:
    SELECT [d].[Id], [d].[Notes], [d].[Stars], [d].[Title]
          FROM [Dishes] AS [d]
          WHERE [d].[Title] LIKE N'F%'

    a) method StartsWith("F") is tranlated by EF to:
        WHERE [d].[Title] LIKE N'F%'

    b) What in general happens, when we write a LINQ query:
       -c# translate LINQ query to intermediate language
       -then, copiled by the JIT compiler to Assembly languate
       -then, executed !

    c) But steps "c" no longer true, because we need to translate
       the Linq query to a "sql language" not to a machine language
       -So, somehow, EF must inpect the LINQ query, and do the translation
        to a "sql query", not allowing the compiler do it. 
        How/Where/When does it do it ?
        Answer: 
        c1) code is compiled normally by c#
        c2) at run-time, EF manages to translate the compiled c#
            code into SQL code

    d) Via expression - compiled code shows the original query content
       (in source code), then, EF is able to inspect it and generate
       the SQL query necessary:
       e.g.:
       d1) lambda expression compiled
           Func<Dish, bool> f = d => d.Title.StartsWith("F");
           compiled as: f = {Method = {Boolean <<Main>$>b__0_9(Dish)}}

       d2) expression compiled:
           Expression<Func<Dish, bool>> exp = d => d.Title.StartsWith("F");
           compiled as EXPRESSION TREE: {d => d.Title.StartsWith("F")} (*)
           (*) and this is exactly the original LINQ query - where

        e) EF (and other tools) are able to inspect the expression tree (generated 
            by the c# compiler) at runtime and convert it in the SQL command
           (*) When EF analyses the exp. tree and see that there is a
               StartsWith, it translate it to a "LIKE" in SQL!

        (**) conclusion: Where clauses are compiled into an EXPRESSION TREE
             that will be used at runtime by EF to generate the corresponding
             SQL command.

    -LINQ queries - for DB and in memory - where clauses

    a) LINQ + EF query
    var dishes = await dbContext.Dishes
            .Where(d => d.Title.StartsWith("F"))
            .ToArrayAsync();
    Where clause compiled to:
    public static IQueryable<TSource> Where<TSource>(this IQueryable<TSource> source, Expression<Func<TSource, bool>> predicate);
    
    (*) it takes an Expression tree - so, after compilation, EF will be use the expression
        tree to generate the corresponding SQL query to execute it !.

    b) LINQ + in memory query
    var allInmemoryDishes = inmemoryDishes
            .Where(d => d.Title.StartsWith("F"))
            .ToArray();
    Where clause compiled to:
    public static IEnumerable<TSource> Where<TSource>(this IEnumerable<TSource> source, Func<TSource, bool> predicate);
    
    (*) it takes a function directly (not an expression) - so, it will be executed normally after compilation
             
}

*/

//--- db queries ---
var factory = new CookbookContextFactory();
using var dbContext = factory.CreateDbContext(args);

var newDish = new Dish {Title="Foo", Notes="Bar" };
//wil leads to an insert in the db
dbContext.Dishes.Add(newDish);
await dbContext.SaveChangesAsync();
newDish.Notes = "Baz";
//EF - generated a sql updating only the Notes here,
//and nothing else - how does it know which
//fields were modified?
//A: he keeps the orginal object read
//in the db & compares versus modified version
await dbContext.SaveChangesAsync();

//----------------------------------------------
await EntityStates(factory, args);

static async Task EntityStates(CookbookContextFactory factory, string [] args)
{
    using var dbContext = factory.CreateDbContext(args);

    var newDish = new Dish { Title = "Foo", Notes = "Bar" };

    //state (initial) = detached -> object unknown by EF - not in the DB yet
    var state = dbContext.Entry(newDish).State;

    // state = Added
    // now - object is NOT IN DB yet, but EF
    // but EF knows about it (after the Add in dbContext)
    dbContext.Dishes.Add(newDish);
    state = dbContext.Entry(newDish).State; // state = Added

    // state = unchanged
    // object was written in the DB, and there is
    // so, now, there is no differences between
    // the object in memory (newDish - being tracked by EF
    // and the one saved in the DB)
    await dbContext.SaveChangesAsync();
    state = dbContext.Entry(newDish).State; // state = Unchanged

    // state = Modified
    // when we change the content of a tracked object
    // e.g.: newDish.Notes = "Baz";
    newDish.Notes = "Baz";
    state = dbContext.Entry(newDish).State; // state = Modified

    // State = Unchanged again, after the Save...
    await dbContext.SaveChangesAsync();
    state = dbContext.Entry(newDish).State; // state = Unchanged

    // state = Deleted
    // after we delete the in memory obj. under
    // EF control.
    dbContext.Dishes.Remove(newDish);
    state = dbContext.Entry(newDish).State; // state = Deleted

    // state = Detached  -> no connection with EF anymore
    // when the Deleted object (in memory) is finally
    // removed from the DB
    await dbContext.SaveChangesAsync();
    state = dbContext.Entry(newDish).State; // state = Detached
}

//
//--- change tracking by EF ---
//

//----------------------------------------------
await ChangeTracking(factory, args);

static async Task ChangeTracking(CookbookContextFactory factory, string[] args)
{
    using var dbContext = factory.CreateDbContext(args);

    var newDish = new Dish { Title = "Foo", Notes = "Bar" };
    dbContext.Dishes.Add(newDish);
    await dbContext.SaveChangesAsync();

    //changing entity content 
    newDish.Notes = "Baz";

    //entry has lots of interesting properties &
    //methods - TODO: check them later!
    var entry = dbContext.Entry(newDish);

    //VIP: at this point, originalValue => Notes = "Bar"
    //as this is the actual value written in the database !!!
    var originalValue = entry.OriginalValues[nameof(Dish.Notes)].ToString();

    //here, during the save(if I run it), EF will verify that
    //only Notes field was changed, so, it will build
    //an update query having just Notes in it
    // e.g:
    //   UPDATE [Dishes] SET [Notes] = @p0
    //   WHERE[Id] = @p1;
    //await dbContext.SaveChangesAsync();
    // (*) if I had executed SaveChangesAsync() above,
    //     the originalValue for this field, in memory,
    //     would be updated to reflect the content of the
    //     database.

    // using a new/another dbContext

    //as Notes for dbContext WAS NOT SAVED in the DB,
    //the query below will return the value IN MEMORY
    //as the entity was modified (and will not go to
    // the database to get this info)
    //below, originalValue=BAZ -> the actual value in the entity
    //       (not the value in the database)
    originalValue = entry.OriginalValues[nameof(Dish.Notes)].ToString();
    var dishFromDatabse = await dbContext.Dishes
        .SingleAsync(d => d.Id == newDish.Id);

    // using a new/another dbContext
    // the query below will return Bar -> the actal value in
    // the DB, as dbContext2 is new, so, was not modified !
    var dbContext2 = factory.CreateDbContext(args);
    var dishFromDatabse2 = await dbContext2.Dishes
        .SingleAsync(d => d.Id == newDish.Id);
    var entry2 = dbContext2.Entry(newDish);
    var originalValue2 = entry2.OriginalValues[nameof(Dish.Notes)].ToString();

    originalValue = entry.OriginalValues[nameof(Dish.Notes)].ToString();
}

//
//--- No Tracking ---
//

//----------------------------------------------
await NoTracking(factory, args);

static async Task NoTracking(CookbookContextFactory factory, string[] args)
{
    using var dbContext = factory.CreateDbContext(args);

    // get all dishes from the DB
    // after this command, all dishes from the database
    // table(Dishes) is added to the changing tracker !!!
    // this is necessary (to kind of initialize the changing
    // tracker process - the originalValues) but can be heavy (hit in performance)
    // state below = Unchanged
    var dishes = await dbContext.Dishes.ToArrayAsync();
    var state = dbContext.Entry(dishes[0]).State;

    //BUT - in case we don't need to track changes in this case,
    // we will need the data for just generate a report for instance,
    // no need to changes in DB?
    // use AsNotracking option
    // state below = Detached
    var dishesNoTrck = await dbContext.Dishes.AsNoTracking().ToArrayAsync();
    var stateNoTrck = dbContext.Entry(dishesNoTrck[0]).State;
}

//----------------------------------------------
await AttachEntities(factory, args);

static async Task AttachEntities(CookbookContextFactory factory, string[] args)
{
    using var dbContext = factory.CreateDbContext(args);

    var newDish = new Dish { Title = "Foo", Notes = "Bar" };
    dbContext.Dishes.Add(newDish);
    await dbContext.SaveChangesAsync();
    //below -> State = Unchanged
    var state = dbContext.Entry(newDish).State;

    //make EF to forget about an object it is tracking
    //force it to - Detached state
    dbContext.Entry(newDish).State = EntityState.Detached;

    //below -> State = Detached
    var state2 = dbContext.Entry(newDish).State;

    //Update method - if Detached obj/entity,
    //EF will:
    //-add it to the change tracker
    //-if I run a Save... -> EF will overrite the obj
    // in the DB (all the fields)
    dbContext.Dishes.Update(newDish);
    await dbContext.SaveChangesAsync();

}

//--- executing RAW sql queries ---
await RawSql(factory, args);

static async Task RawSql(CookbookContextFactory factory, string[] args)
{
    using var dbContext = factory.CreateDbContext(args);
    
    //raw queries 
    //we are still in EF world control -
    //so, I will get back entity objects
    //tracked by EF
    //(*) The prefered to generate queries should
    //    be always FIRST via LINQ
    var dishes = await dbContext.Dishes
        .FromSqlRaw("SELECT * from Dishes")
        .ToArrayAsync();
    
    //state = Unchanged !!! so, still managed by EF's changes tracker
    var state = dbContext.Entry(dishes[0]).State;

    //raw queries using/passing PARAMETERS
    var filter = "B%";
    var dishes2 = await dbContext.Dishes
        .FromSqlInterpolated($"SELECT * from Dishes WHERE Notes LIKE {filter}")
        .ToArrayAsync();

    //BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD
    //BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD
    //Example of query vulnerable to SQL INJECTION
    var filter3 = "B%; DROP TABLE xyz";
    var dishes3 = await dbContext.Dishes
        .FromSqlRaw("SELECT * from Dishes WHERE Notes LIKE '"+filter3+"'")
        .ToArrayAsync();
    //BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD

    //Raw Queries + WRITING statements (delete, update, etc)
    await dbContext.Database.ExecuteSqlRawAsync
        ("DELETE FROM Dishes WHERE Id <= 20");
}

//--- transactions ---
await Transactions(factory, args);

static async Task Transactions(CookbookContextFactory factory, string[] args)
{
    using var dbContext = factory.CreateDbContext(args);

    // transactions - steps to build it
    // a) add the whole block in a try/catch block
    // b) start the transacation before the try/catch block
    //    e.g.:
    //    using var transaction = await dbContext.Database.BeginTransactionAsync();
    // c) commit/end the transaction, at the end of the try block
    //    e.g.:
    //    transaction.Commit();
    //    (*) if an exception occurs, an
    //        automatic rollback will occurs (via using)
    //        as we end the try/catch block without
    //        doing a commit

    using var transaction = await dbContext.Database.BeginTransactionAsync();
    try
    {
        dbContext.Dishes.Add(new Dish { Title = "Foo", Notes = "Bar" });
        await dbContext.SaveChangesAsync();

        //sql query to generate an error - 0 division
        //var dishes = await dbContext.Dishes
        //    .FromSqlRaw("SELECT 1/0")
        //    .ToArrayAsync();

        //end the transaction
        transaction.Commit();
    }
    catch (Microsoft.Data.SqlClient.SqlException e)
    {
        Console.WriteLine($"ERROR - exception info={e.Message}");
    }
}

//--- expression trees (advanced)---
await ExpressionTree(factory, args);

static async Task ExpressionTree(CookbookContextFactory factory, string[] args)
{
    using var dbContext = factory.CreateDbContext(args);

    var newDish = new Dish { Title = "Foo", Notes = "Bar" };
    dbContext.Dishes.Add(newDish);
    await dbContext.SaveChangesAsync();
    // this is the sql query generated by EF for the Linq query below:
    //  SELECT[d].[Id], [d].[Notes], [d].[Stars], [d].[Title]
    //  FROM[Dishes] AS[d]
    //  WHERE[d].[Title] LIKE N'F%'

    //LINQ - EF query
    //compilatation will generate an expression tree, that later
    //will be translated, by EF, to a sql query to execute it !
    var dishes = await dbContext.Dishes
        .Where(d => d.Title.StartsWith("F"))
        .ToArrayAsync();

    //lambda expression
    Func<Dish, bool> f               = d => d.Title.StartsWith("F");
    Expression<Func<Dish, bool>> exp = d => d.Title.StartsWith("F");

    //LINQ - in memory query
    //query will run normally after compilation
    //(no other translation requered)
    var inmemoryDishes = new[]
    {
        new Dish { Title = "Foo", Notes = "Bar" },
        new Dish { Title = "Foo", Notes = "Bar" }
    };
    var allInmemoryDishes = inmemoryDishes
        .Where(d => d.Title.StartsWith("F"))
        .ToArray();
}


//--- class definitions ---

//-------------------------------------------
//- model
//-------------------------------------------
class Dish
    {
        //will be PK auto increment field in db table
        public int Id { get; set; }

        //using string -> so in DB Title will NOT BE NULLABLE
        //if it was string? -> field created in DB would be NULLABLE
        //? -> means optional in C# and NULLABLE in DB
        //using annotation to specify size (varchar) in DB
        [MaxLength(100)]
        public string Title { get; set; } = string.Empty;

        //optional field -> ?
        [MaxLength(1000)]
        public string? Notes { get; set; }

        //optional field -> ?
        public int? Stars { get; set; }

        //A Dish can have many ingredients 
        //modelin 1:N relationship
        public List<DishIngredients> Ingredients { get; set; } = new List<DishIngredients>();

    }

    class DishIngredients
    {
        //will/generate be PK auto increment field in db table
        public int Id { get; set; }

        [MaxLength(100)]
        public string Description { get; set; } = string.Empty;

        [MaxLength(50)]
        public string UnitOfMeasure { get; set; } = string.Empty;

        //for the DB side we need to inform number of decimals + number of digits
        //"decimal(5,2)" is the info for SQL Server, via annotation (no need in c# side)
        [Column(TypeName = "decimal(5,2)")]
        public decimal Amount { get; set; }

        //1 ingredient relates to 1 dish
        //we are on the 1 side of the relationship
        //there only 1 dish that the DishIngredients
        //relates to
        // this is the navegation property(*)

        public Dish? Dish { get; set; }

        //VIP: FK -> define relation DishIngredients with Dish
        public int DishId { get; set; }
    }

    //-------------------------------------------
    //- context
    //-------------------------------------------
    //--- DBContext ---
    //requires a nugget package: Microsoft.EntityFrameworkCore.SqlServer
    class CookbookContext : DbContext
    {
        //DbSet<Dish> -> represents a table in the db that is queryable!
        //via SQL (db) or Linq (in c#)
        //implements: IQueryable and IEnumerable(used by LINQ)
        public DbSet<Dish> Dishes { get; set; }
        public DbSet<DishIngredients> Ingredients { get; set; }

        public CookbookContext(DbContextOptions<CookbookContext> options)
            : base(options)
        { }
    }

    //-------------------------------------------
    //- context factory 
    //- (required only for console apps)
    //-------------------------------------------
    class CookbookContextFactory : IDesignTimeDbContextFactory<CookbookContext>
    {
        public CookbookContext CreateDbContext(string[] args)
        {
            var configuration = new ConfigurationBuilder().AddJsonFile("appsettings.json").Build();

            var optionsBuilder = new DbContextOptionsBuilder<CookbookContext>();
            optionsBuilder
                // to print generated SQL statements on the console.
                .UseLoggerFactory(LoggerFactory.Create(builder => builder.AddConsole()))
                //Use{dbtype}: e.g. UseSqlServer, UsePostgress, etc
                //we need here to specigy a connection string, so that
                //EF can find/connect to the database
                //VIP: NEVER write directly a conn. string in c# code,
                //     because it can have sensitive data (login, pwd, etc)
                //     solution: use a configuration file - txt (add it to the project)
                .UseSqlServer(configuration["ConnectionStrings:DefaultConnection"]);

            return new CookbookContext(optionsBuilder.Options);
        }
    }



