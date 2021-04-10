using System;
using System.IO;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using System.Linq;
using System.Collections.Generic;

//.net5.0 -> no need main + namespace for tests

// Json serialization:
// - Newtonsoft.Json -> not used anymore
//   use System.Text.Json instead !!!

// How GroupBy works:
// eg. car.GroupBy(car => car.Make)
// 1) first, it sorts data by the column you want to groupe
//    (car.Make, in the example)
// 2) it goes to all distinct items, and put them in a group
//    (it generates Group Keys column - unique - pointing to the Key of
//     the original data - car.Model in this example
// 3) remove all duplications in the grop key generated
//    this way, we will have one Group Key item pointing
//    to the original data (N items) - 1:N relationship
//     
//-------------------------------------------
async Task<CarData[]> DeserializeJsonFileAsync()
{
    const string FilePath = "D:\\gitrepo\\studies\\csharp\\LinqOperators\\data.json";

    var fileContent = await 
        File.ReadAllTextAsync(FilePath);
    var cars = JsonSerializer.Deserialize<CarData[]>(fileContent);

    return cars;
}

//-------------------------------------------
void DisplayCars(IEnumerable<CarData> cars, int maxNumber)
{
    Console.WriteLine($"list of cars available...");
    Console.WriteLine($"Printing at most -> {maxNumber} of the total found={cars.Count()}");

    int i = 0;
    foreach (var car in cars)
    {
        Console.WriteLine($"id={car.ID}; make={car.Make}; model={car.Model}; year={car.Year}; number_doors={car.NumberOfDoors}; hp={car.HP}");
        if ((++i) >= maxNumber)
            break;
    }

}

void DisplayCarsFromString(IEnumerable<string> cars, string label, int maxNumber)
{
    Console.WriteLine($"list of cars available...");
    Console.WriteLine($"Printing at most -> {maxNumber} of the total found={cars.Count()}");

    //int i = 0;
    //Console.WriteLine($"   {0}", String.Join(" ", cars));

    var i = 0;
    foreach (var car in cars)
    {
        //var tmp = car.split(" ");
        Console.WriteLine($"{label} -> {car}");
        if ((++i) >= maxNumber)
            break;
    }
    //Console.WriteLine($"{String.Join("\n", cars)}");
}


//-------------------------------------------
void LinqPrintAtLeastCars4Doors(CarData[] cars)
{
    var carsWithAtLeast4Doors =
        cars.Where(cars => cars.NumberOfDoors >= 4);

    DisplayCars(carsWithAtLeast4Doors, 1000);
}

//-------------------------------------------
void LinqPrintAllMazdaWithAtLeastCars4Doors(CarData[] cars)
{
    var result = cars
            // slightly more performant !!!
            //.Where(car => car.NumberOfDoors >= 4 && car.Make.Equals("Mazda"));
            // OR
            .Where(car => car.NumberOfDoors >= 4)
            .Where(car => car.Make.Equals("Mazda"));

    DisplayCars(result, 1000);
}

//-------------------------------------------
void LinqPrintAllMakesStartsWithM(CarData[] cars)
{
    /*
    //OPTION-1 -> creating a var. with results, then, print results
    var result = cars
            .Where(car => car.Make.StartsWith("M"))
            // projection - get only part of the CarData fields
            // were are projecting the CarData to a string
            // after the select - we don't have an IEnumerable of
            // CarData anymore - but a IEnumerable of string
            .Select(car => $"{car.Make} {car.Model}")
            // ToList -> returns a List<string> - which is
            // an IEnumerable !!!
            .ToList();
    DisplayCarsFromString(result, "make/model", 1000);
    */

    //OPTION-2 -> query display results automaticaly
    //            no need of variable (to print later)
    cars
    .Where(car => car.Make.StartsWith("M"))
    // projection - get only part of the CarData fields
    // were are projecting the CarData to a string
    // after the select - we don't have an IEnumerable of
    // CarData anymore - but a IEnumerable of string
    .Select(car => $"{car.Make} {car.Model}")
    // ToList -> returns a List<string> - which is
    // an IEnumerable !!!
    .ToList()
    //ForEach available only in List (NOT in IEnumerable)
    //so, to use ForEach we need the ToList()
    //ForEach -> does not return anything - is an action
    .ForEach(car => Console.WriteLine(car));
}

//-------------------------------------------
//Display a list of the 10 most powerful cars in
//terms of HP - show make + model
void LinqPrint10MostPowerful(CarData[] cars)
{
    cars
    .OrderByDescending(car => car.HP)
    .Take(10)
    .Select(car => $"{car.Make}; {car.Model}; {car.HP}")
    .ToList()
    .ForEach(car => Console.WriteLine(car));
}

//---GroupBy---

//-------------------------------------------
//Display the number of models per make that appears
//after 1995
void LinqPrintModelsPerMakeAfter1995(CarData[] cars)
{
    cars
    // the result of a GroupBy is an:
    // IEnumerable<IGrouping<string, CarData>>
    // string = auto generated unique Key (make) for grouping
    // so, per Make, we have a collection of CarData
    // so, we have in the grouping:
    // one make -> pointing to a collection of CarData belonging to that make !
    .Where(car => car.Year > 1995)
    .GroupBy(car => car.Make)
    /*
    //shows all the grouping keys generate by this GroupBy = all unique/distinct car makes
    .ForEach(grp => Console.WriteLine(grp.Key));
    */
    // do a projection - to get the make + number of models (via Count)
    //.Select(grp => $"{grp.Key} -> {grp.Count<CarData>()}")

    //OR - using anonymous class
    .Select(grp => new { TheMake = grp.Key, TheNumberOfModels = grp.Count() })
    .ToList()
    //.ForEach(item => Console.WriteLine(car));
    .ForEach(item => Console.WriteLine($"{item.TheMake} -> {item.TheNumberOfModels}"));
}

//-------------------------------------------
// Display the number of models per make that appears
// after 2008 & makes should appear with 0 with
// there are no models for the selected year
void LinqPrintModelsPerMakeAfter2008Zeroes(CarData[] cars)
{
    cars.GroupBy(car => car.Make)
    //OR - using anonymous class
        .Select(grp => new 
        {   TheMake = grp.Key,
            // grp.Where - similar to having - filter inside the group
            //TheNumberOfModels = grp.Where(car => car.Year >= 2008).Count()

            //OR samething but SIMPLER
            TheNumberOfModels = grp.Count(car => car.Year >= 2008)
        })
        .ToList()
        .ForEach(item => Console.WriteLine($"{item.TheMake} -> {item.TheNumberOfModels}"));
}

//-----------------------------------------------
//Display a list of makes that have at least 2 models
//that appears after 1995
void LinqPrintAtLeast2ModelsAfter1995(CarData[] cars)
{
    cars.Where(car => car.Year > 1995)
        .GroupBy(car => car.Make)
        .Select(grp => new
        {
            TheMake = grp.Key,
            //OR samething but SIMPLER
            TheNumberOfModels = grp.Count()
        })
        .Where(grp => grp.TheNumberOfModels >=2)
        .ToList()
        .ForEach(item => Console.WriteLine($"{item.TheMake} -> {item.TheNumberOfModels}"));
}

//-----------------------------------------------
//Display a list of makes that have at least 2 models
//with >= 400 HP
void LinqPrintAtLeast2Models400HP(CarData[] cars)
{
    cars.Where(car => car.HP >= 400)
        .GroupBy(car => car.Make)
        .Select(grp => new
        {
            TheMake = grp.Key,
            //OR samething but SIMPLER
            TheNumberOfModels = grp.Count()
        })
        //this is similar to a having - in sql
        .Where(grp => grp.TheNumberOfModels >= 2)
        .ToList()
        .ForEach(item => Console.WriteLine($"{item.TheMake} -> {item.TheNumberOfModels}"));
}

//-----------------------------------------------
//Display a list of makes that have at least 2 models
//with >= 400 HP
void LinqPrintAvgHPPerMake(CarData[] cars)
{
    cars.GroupBy(car => car.Make)
        .Select(grp => new
        {
            TheMake = grp.Key,
            //OR samething but SIMPLER
            TheAverageHp = grp.Average(grp => grp.HP)
        })
        //this is similar to a having - in sql
        .ToList()
        .ForEach(item => Console.WriteLine($"{item.TheMake} -> {item.TheAverageHp}"));
}

//-----------------------------------------------
//Display how many makes build cars with
//horse power
//between 00..100, 101..200, 201..300, 301..400, 401..500
void LinqPrintHPInRange(CarData[] cars)
{
    cars.GroupBy(car => car.HP switch
        {
            //building groups based on a calculated
            //expression/vale

            //the sintaxe below is c#9 - switch expression
            <= 100 => "000..100",
            <= 200 => "101..200",
            <= 300 => "201..300",
            <= 400 => "301..400",
            _ =>      "401..500" //else
        })
        .Select(grp => new
        {
            HPCategory = grp.Key, 
            NumberOfMaques = grp.Distinct().Count()
        })
        .OrderBy(grp => grp.HPCategory)
        //this is similar to a having - in sql
        .ToList()
        .ForEach(item => Console.WriteLine($"{item.HPCategory} -> {item.NumberOfMaques}"));
}


//--- main calls ---
//-----------------------------------------------
Console.WriteLine("___________________________");
Console.WriteLine(">>>>>using DeserializeJsonFileAsync...");
var allCars = await DeserializeJsonFileAsync();
Console.WriteLine($"json file content...");
DisplayCars(allCars, 10);

Console.WriteLine("___________________________");
Console.WriteLine(">>>>>using LinqPrintAtLeastCars4Doors()...");
var allCars2 = await DeserializeJsonFileAsync();
LinqPrintAtLeastCars4Doors(allCars2);

Console.WriteLine("___________________________");
Console.WriteLine(">>>>>using LinqPrintAllMazdaWithAtLeastCars4Doors()...");
var allCars3 = await DeserializeJsonFileAsync();
LinqPrintAllMazdaWithAtLeastCars4Doors(allCars3);

Console.WriteLine("___________________________");
Console.WriteLine(">>>>>using LinqPrintAllMakesStartsWithM()...");
var allCars4 = await DeserializeJsonFileAsync();
LinqPrintAllMakesStartsWithM(allCars4);

Console.WriteLine("___________________________");
Console.WriteLine(">>>>>using LinqPrint10MostPowerful()...");
var allCars5 = await DeserializeJsonFileAsync();
LinqPrint10MostPowerful(allCars5);

Console.WriteLine("___________________________");
Console.WriteLine(">>>>>using LinqPrintModelsPerMakeAfter1959()...");
var allCars6 = await DeserializeJsonFileAsync();
LinqPrintModelsPerMakeAfter1995(allCars6);

Console.WriteLine("___________________________");
Console.WriteLine(">>>>>using LinqPrintModelsPerMakeAfter2008Zeroes()...");
var allCars7 = await DeserializeJsonFileAsync();
LinqPrintModelsPerMakeAfter2008Zeroes(allCars7);

Console.WriteLine("___________________________");
Console.WriteLine(">>>>>using LinqPrintAtLeast2ModelsAfter1995()...");
var allCars8 = await DeserializeJsonFileAsync();
LinqPrintAtLeast2ModelsAfter1995(allCars8);

Console.WriteLine("___________________________");
Console.WriteLine(">>>>>using LinqPrintAtLeast2Models400HP()...");
var allCars9 = await DeserializeJsonFileAsync();
LinqPrintAtLeast2Models400HP(allCars9);

Console.WriteLine("___________________________");
Console.WriteLine(">>>>>using LinqPrintAvgHPPerMake()...");
var allCars10 = await DeserializeJsonFileAsync();
LinqPrintAvgHPPerMake(allCars10);

Console.WriteLine("___________________________");
Console.WriteLine(">>>>>using LinqPrintHPInRange()...");
var allCars11 = await DeserializeJsonFileAsync();
LinqPrintHPInRange(allCars11);


//-------------------------------------------
class CarData
{
    //the name of the property in json file is different - so, we fix vai [JsonProperty...]
    [JsonPropertyName("id")]
    public int ID { get; set; }

    [JsonPropertyName("car_make")]
    public string Make { get; set; }

    [JsonPropertyName("car_models")]
    public string Model { get; set; }

    [JsonPropertyName("car_year")]
    public int Year { get; set; }

    [JsonPropertyName("number_of_doors")]
    public int NumberOfDoors { get; set; }

    [JsonPropertyName("hp")]
    public int HP { get; set; }
}

