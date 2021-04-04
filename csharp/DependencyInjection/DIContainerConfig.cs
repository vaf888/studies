using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using Autofac;
using DemoLibrary;
using DemoLibrary.Utilities;

namespace DependencyInjection
{
    public static class DIContainerConfig
    {
        //method used to configure the container
        //container will have all the classes (key pair list)
        //that we want to instantiate
        public static IContainer Configure()
        {
            var builder = new ContainerBuilder();

            //registering types
            //it means: when you look for a IDIBusinessLogic instance interface
            //          return one instance of DIBusinessLogic()
            builder.RegisterType<DIBetterBusinessLogic>().As<IDIBusinessLogic>();
            builder.RegisterType<DIApplication>().As<IDIApplication>();
            builder.RegisterType<DIDataAccess>().As<IDIDataAccess>();
            builder.RegisterType<DILogger>().As<IDILogger>();

            // one way - hard if we had lots of classes to instantiate
            //builder.RegisterType<DILogger>().As<IDILogger>();
            //builder.RegisterType<DIDataAccess>().As<IDIDataAccess>();

            /* ---TODO: fix exception below ---
            //another way - simpler - added all classes in one directory Utilies
            // and use RegisterAssemblyTypes, as follows:
            builder.RegisterAssemblyTypes(Assembly.Load(nameof(DemoLibrary)))
                .Where(t => t.Namespace.Contains("Utilities")) // namespace contains Utilities
                //below means: in the Utilities folder, get all classes, and then
                // link them up to their matching interface;
                // e.g.: if you find an DIDataAccess class look for the IDIDataAccess
                //       interface
                .As(t => t.GetInterfaces().FirstOrDefault(i => i.Name == "I" + t.Name));
            */

            return builder.Build();
        }
    }
}
