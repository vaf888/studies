using DemoLibrary.Utilities;
using System;
using System.Collections.Generic;
using System.Text;

namespace DemoLibrary
{
    class DIBetterBusinessLogic : IDIBusinessLogic
    {
        IDILogger _logger;
        IDIDataAccess _dataAccess;

        public DIBetterBusinessLogic(IDILogger logger, IDIDataAccess dataAccess)
        {
            _logger = logger;
            _dataAccess = dataAccess;
        }

        public void ProcessData()
        {
            Console.WriteLine("_______________________________________");
            _logger.Log("Starting the processing of data...");
            Console.WriteLine("Processing the data.");
            _dataAccess.LoadData();
            _dataAccess.SaveData("Information processed !");
            _logger.Log("Finished processing of the data.");
            Console.WriteLine("_______________________________________");
        }
    }
}
