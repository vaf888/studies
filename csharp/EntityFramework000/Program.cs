using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Design;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;

/*
---Entity Framework (EF)---
a0) add in project config <Nullable>enable</Nullable>
to accept nullable fiels -> type ? fieldName

a)using pre-installed sqllocaldb
run -> sqllocaldb i    -> to show available server
answer: MSSQLLocalDB

b) Id property -> EF will create id field (primary key)  in table auto increment

c) navegation property(*)
   A navigation property is an optional property
   on an entity type that allows for navigation 
   from one end of an association to the other end. 
   Unlike other properties, navigation properties 
   do not carry data.
   E.g.:
   Customer.Orders property (List) -> travels from a customer to its collection of orders
           (*) we can take all orders from customer
   Order.Customer property -> rerturns a single obj, the customer linked to the order.
           (*) called scalar navig. or refer. navig. property

d) DbContext
   -An instance of DbContext represents a session 
    with the database which can be used to query and save instances 
    of your entities to a database. 
   -DbContext is a combination of the Unit Of 
    Work and Repository patterns.
   -DbContext in EF Core allows us to perform following tasks:
    Manage database connection, Configure model & relationship
    Querying database, Saving data to the database
    Configure change tracking, Caching, Transaction management
   -To use DbContext in our application, we need
    to create the class that derives from DbContext, 
    also known as context class.

e) requires a nugget package: Microsoft.EntityFrameworkCore.SqlServer

f) DbSet<Dish>
   -represents a table in the db that is queryable!
    via SQL (db) or Linq (in c#)
   -implements: IQueryable and IEnumerable(used by LINQ)
g) Factory Method (e.g.: CookbookContextFactory)
   -needed only for console application
   -for WebAPI, ASP, etc - no need - it will created automaticaly

h) To read *appsettings.json*, add: `dotnet add package Microsoft.Extensions.Configuration.Json`
   Only required for console apps
   (*) Note: Not necessary in ASP.NET, WebAPI, etc.
   (**) - appproperties.json -> change its property to copy it to output file
i) add NuGet package: Microsoft.EntityFrameworkCore.Design

j) generate database from DbContext
   i1) a ONE TIME ONLY install step:
       Install EF Tools globally - via dos command
       dotnet tool install --global dotnet-ef

k) Creating a database from our c# classes:
   ..Migrations:
     -take your changes in c# classes and migrate them
      into the database (by generating behind the scenes: create table,
      alter tables statements, etc.)
   ..EF can generate the schema(code to generate tables in the db)
     from the c# classes - via migrations code !
   ..Migrations because:
     -it migrates the db code (schema) from one version to the other
     -the FIRST TIME, as there are no tables in the DB - migrations
      will create them
     -we need to rerun migrations each time we do changes
      in the c# classes that must update the db schema (db tables)
      e.g.: adding a new table, adding a new column to a table, etc

k1) Running Migrations - to generate the code necessary to create/alter the database
    ..Open a dos command line in the project directory (e.g.:
      D:\gitrepo\studies\csharp\EntityFramework000) & run:
        dotnet ef migrations add Initial
        (*) Initial = any name
        (**) after execution, it will create the
             directory migrations in the project
             whith the code to generate db tables, etc

k2) Create/modify DB - using the migration code (from K1)
    -again, in the project directory + command line...

    1) make EF display (not run) the commands it will
       run/execute into the database:
       dotnet ef migrations script
       (*) in case we need to change the db - we
           need to change de c# class, create a new migration, etc

    2) Run the command below to create the database/update:
       (it will: compile our app, run the script  apllying
        migrations)
        -> dotnet ef database update

l) download + install Azure Data Studio - as a tool to manage database
   https://docs.microsoft.com/en-us/sql/azure-data-studio/download-azure-data-studio?view=sql-server-ver15#download-the-latest-release
   (*) to configure connection to the db use in server:
       (localdb)\MSSQLLocalDB

m) LINQ queries + DB access:
   -VIP(1): LINQ query - NOT EXECUTED immediately - needs
            to be used/iterated via: foreach, ToList, ToArray, count, writeline, etc.
   -VIP(2): now we are accessing DB - so ALWAYS USE ASYNC methods
    e.g.:
        var dishes = await context.Dishes
        .Where(d => d.Title.Contains("rrid"))
        .ToListAsync();

n) How to turn log in - so that we can see the command
   issue into the database
   add the NuGet package:
   Microsoft.Extensions.Logging.Console
   (*) And, in the dbcontext factory add:
       .UseLoggerFactory(LoggerFactory.Create(builder => builder.AddConsole()))
   (**) show sql commands executed in the console !

*/

//--- db queries ---
var factory = new CookbookContextFactory();
using var context = factory.CreateDbContext(args);

//----------------------------------------------
//-INSERT/add entry dish to db

//NEVER set the Id property in this case - it is auto-generated!!!
var porridge = new Dish {Title="breakfast porridge", 
    Notes="this is so good", Stars=4 };

//VIP: add does not run immediately - we could add other
//     stuff here (it just register changes to be added
//     to the db - e.g. via SaveChangesAsync
context.Dishes.Add(porridge);

//this will run the command and write into the database
await context.SaveChangesAsync();
Console.WriteLine("______________________________________");
Console.WriteLine($">>>>>added porridge to the database; id={porridge.Id}");

//----------------------------------------------
//-UPDATE entry from to db
Console.WriteLine($">>>>>updating item from the db; id={porridge.Id}...");
Console.WriteLine($">>>>>before update - Stars={porridge.Stars}");
porridge.Stars = 3;
await context.SaveChangesAsync();
Console.WriteLine(">>>>>Update done !!!");
Console.WriteLine($">>>>>after update - Stars={porridge.Stars}");

//----------------------------------------------
//-Querying data
Console.WriteLine($">>>>>Checking stars for porridge...");
//we want to read again it from db (we have it in memory)
//this is a LINQ query & it is translated to SQL
//behind the scenes
//VIP(1): LINQ query - NOT EXECUTED immediately - needs
//     to be used/iterated via: foreach, ToList, ToArray, count, writeline, etc.
//VIP(2): now we are accessing DB - so ALWAYS USE ASYNC methods
var dishes = await context.Dishes
    .Where(d => d.Title.Contains("rrid"))
    .ToListAsync();
if (dishes.Count != 1)
    Console.WriteLine($">>>>>ERROR - could not get a dish!!!");
else
    Console.WriteLine($">>>>>Found dish in the db; Id={dishes[0].Id}; Title={dishes[0].Title}");

//----------------------------------------------
//-DELETE entry from to db
Console.WriteLine($">>>>>deleting item from the db; id={porridge.Id}...");
context.Dishes.Remove(porridge);
await context.SaveChangesAsync();
Console.WriteLine(">>>>>deleted!!!");






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



