using DemoLibrary;
using System;
using System.Collections.Generic;
using System.Text;

namespace DependencyInjection
{

    // will start up everything
    public class DIApplication : IDIApplication
    {
        IDIBusinessLogic _businessLogic;

        public DIApplication(IDIBusinessLogic bl)
        {
            _businessLogic = bl;
        }

        public void Run()
        {

            // Autofac follows the following logic:
            // creates the full graph of object dependencies
            // based on the constructor of each object in the call graph.
            // e.g.:
            //   1-DIApplication (was instantiated in Main)
            //   2-depends/calls on  IDIBUsinessLogic in the constructor
            //      3-depends on  IDILogger and IDIDataAccess via constructor
            //          3.1-DILogger - no dependencies - create it !
            //          3.2-DIDataAcess - no dependencies - create it !
            //      3-creates DIBUsinessLogic
            //   2-Create DIApplication

            _businessLogic.ProcessData();
        }
    }

}
