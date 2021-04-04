using System;
using System.Collections.Generic;
using System.Text;
using DemoLibrary.Utilities;

namespace DemoLibrary
{
    class DIBusinessLogic : IDIBusinessLogic
    {
        //v1 - using interfaces + stopping depending
        //     on low level classes - using constructor injection

        IDILogger _logger;
        IDIDataAccess _dataAccess;
        public DIBusinessLogic(IDILogger logger, IDIDataAccess dataAccess)
        {
            _logger = logger;
            _dataAccess = dataAccess;
        }
            
        public void ProcessData()
        {
            _logger.Log("Starting the processing of data...");
            Console.WriteLine("Processing the data.");
            _dataAccess.LoadData();
            _dataAccess.SaveData("Information processed !");
            _logger.Log("Finished processing of the data.");
        }

        /*
                --- v0 - DI issues -> using new ---
                public void ProcessData()
                {
                    //Dependency Injection(DI) issues here:
                    //-using new for 2 classes
                    //-so, we havily depend on these 2 classes (coupled)
                    //-this class is directed tied to the 2 utility classes
                    //-we would have to change here also, if we do changes in those 2 classes
                    //-According to DI - this is wrong - we should go levels up (in BusinessLogic,
                    // to control the creation(new) of these objects
                    Logger logger = new Logger();
                    DataAccess dataAccess = new DataAccess();
                    logger.Log("Starting the processing of data...");
                    Console.WriteLine("Processing the data.");
                    dataAccess.LoadData();
                    dataAccess.SaveData("Information processed !");
                    logger.Log("Finished processing of the data.");
                }
        */

    }
}
