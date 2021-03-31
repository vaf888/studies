﻿using System;
using System.Collections.Generic;
using System.IO;
using SolidPrinciples.OpenClosePrincipalOK;
using SolidPrinciples.InterfaceSegregationOK;

namespace SolidPrinciples
{
    /*
       ---SOLID PRINCIPLES---

       -SOLID is an acronym for 5 important design principles when doing OOP (Object Oriented Programming).
       -intention of these principles -> to make your code easier to extend, to understand, to maintain.

       Single responsibility principle
           ..A class should have only one reason to change
           ..Strive for cohesion
           ..Do one thing and do it well
           ..responsibility = ‘reason to change’ -> a class/module should have one, and only one, reason to be changed.

       Open/closed principle
           ..Classes should be open for extension, but closed for modification
           ..Design modules that never change

       Liskov substitution principle
           ..Derived classes must be substitutable/switchable for their base classes
           ..The base class should not have to know about all of its derivatives

       Interface segregation principle
           (*) to avoid: Interface Pollution / Fat Interfaces
           ..Clients should not be forced to depend upon interface that they do not use
           ..no client should be forced to depend on methods it does not use
           ..We don't want "fat" or "polluted" interfaces
             (*) Interfaces that are not specific to a single client leads to unnecessary coupling
                 between clients that would otherwise be isolated
           ..Put more simply: Do not add additional functionality to an existing interface by 
             adding new methods -> Instead, create a new interface and let your class implement 
             multiple interfaces if needed
           ..The Interface Segregation Principle states that no client code object should be forced to depend 
             on methods it does not use. Basically, each code object should only implement what it needs, and 
             not be required to implement anything else.
           ..fat interfaces:
             ...lead to inadvertent couplings between clients that ought to be isolated
             ...can be segregated(separated), through: multiple inheritance, into abstract 
                base classes that break unwanted coupling between components.
                Clients simply mix-in the appropriate interfaces for their activities.

       Dependency inversion principle
           ..Depend on abstractions. Do not depend upon concrete classes
           ..High-level components should not depend on low-level components, both should depend 
             on abstractions
             (*) Abstract classes should not depend upon concrete classes & vice-versa
           ..is a way to decouple software modules.
           ..High-level modules should not depend on low-level modules. Both should depend on abstractions.
           ..Abstractions should not depend on details. Details should depend on abstractions
           ..we need to use: design pattern known as a dependency inversion pattern -> aka dependency injection.
             (*) Typically, dependency injection is used simply by ‘injecting’ any dependencies of a class 
                 through the class’ constructor as an input parameter.
   */

    //--------------------------------------------------------
    public class Database
    {
        public void Add(string msg)
        {
            Console.WriteLine(">>>>>Adding message to database; message={0}", msg);
        }

        public void LogError(string msg, string error)
        {
            Console.WriteLine(">>>>>Logging message to database; error={0}; message={1}", error, msg);
        }

        public void AddAsTag(string postMessage)
        {
            Console.WriteLine(">>>>>Adding tag to database; message={0}", postMessage);
        }

        public void AddComment(string comment)
        {
            Console.WriteLine(">>>>>Adding comment to database; message={0}", comment);
        }

    }

    class SingleResponsibilityBAD
    {
        // method has too many responsibilities:
        // -create a new post
        // -log an error in the database
        // -log an error in a local file.
        //-> This violates the single responsibility principle !
        public void CreatePost(Database db, string postMessage)
        {
            Console.WriteLine(System.Reflection.MethodBase.GetCurrentMethod().Name);

            try
            {
                db.Add(postMessage);
            }
            catch (Exception ex)
            {
                db.LogError("An error occured: ", ex.ToString());
                //File.WriteAllText("LocalErrors.txt", ex.ToString());
            }
        }
    }
    
    //--------------------------------------------------------
    // fix:
    class Log
    {
        public void LogError(string msg, string error)
        {
            Console.WriteLine(">>>>>Logging message to database; error={0}; message={1}", error, msg);
            //File.WriteAllText("LocalErrors.txt", ex.ToString());
        }
    }

    //--------------------------------------------------------
    class SingleResponsibilityOK
    {
        private Log log = new Log();

        public void CreatePost(Database db, string postMessage)
        {
            Console.WriteLine(System.Reflection.MethodBase.GetCurrentMethod().Name);

            try
            {
                db.Add(postMessage);
            }
            catch (Exception ex)
            {
                log.LogError("An error occured: ", ex.ToString());
            }
        }

    }

    //--------------------------------------------------------
    //--- Open/Close principal ---
    //    -(classes, modules, functions, etc.) should be open for extensions, but closed for modification.
    //    -to follow this principal: utilizing inheritance and/or implementing interfaces that enable classes to 
    //     polymorphically substitute for each other.

    // The code below does not follow de Open/Close principal.
    // If we need to also include mentions starting with ‘@’, we’d have to MODIFY the class 
    // with an extra ‘else if’ in the CreatePost() method.
    namespace OpenClosePrincipalBAD
    {
        class Post
        {
            void CreatePost(Database db, string postMessage)
            {
                if (postMessage.StartsWith("#"))
                {
                    db.AddAsTag(postMessage);
                }
                else
                {
                    db.Add(postMessage);
                }
            }
        }
    }

    //code compliant with the open/closed principle by simply using inheritance
    namespace OpenClosePrincipalOK
    {
        interface IPost
        {
            void CreatePost();

            Database Db { get; set; }
            string Message { get; set; }
        }

        class Post : IPost
        {
            public Database Db { get; set; }
            public string Message { get; set; }

            public Post(Database pDb, string pMessage)
            {
                Db = pDb;
                Message = pMessage;
            }

            public void CreatePost()
            {
                Db.Add(Message);
            }
        }

        class TagPost : IPost
        {
            public Database Db { get; set; }
            public string Message { get; set; }

            public TagPost(Database pDb, string pMessage)
            {
                Db = pDb;
                Message = pMessage;
            }

            public void CreatePost()
            {
                Db.AddAsTag(Message);
            }
        }

        class PostComment : IPost
        {
            public Database Db { get; set; }
            public string Message { get; set; }

            public PostComment(Database pDb, string pMessage)
            {
                Db = pDb;
                Message = pMessage;
            }

            public void CreatePost()
            {
                // check if comment valid

                Db.AddComment(Message);
            }
        }

        //L — Liskov substitution principle:
        // a)  if S is a subtype of T, then objects of type T may be replaced (or substituted) with objects of type S.
        // objects in a program should be replaceable with instances of their subtypes without 
        // altering the correctness of that program.
        class PostHandler
        {
            public void HandlePosts(List<IPost> posts)
            {
                Console.WriteLine(System.Reflection.MethodBase.GetCurrentMethod().Name);
                Console.WriteLine("using Liskov substituion...");

                int i = 0;
                foreach (IPost post in posts)
                {
                    Console.WriteLine(">>>>>processing post {0}", ++i);
                    post.CreatePost();
                }
            }
        }
    }

    //--- Interface segregation ---

    /*
        The Interface Segregation Principle states that no client code object should be forced to depend 
        on methods it does not use. Basically, each code object should only implement what it needs, and 
        not be required to implement anything else.         
    */
    public class DataElement
    {
        public void ShowIt()
        {
            Console.WriteLine(System.Reflection.MethodBase.GetCurrentMethod().Name);
            Console.WriteLine(">>>in ShowIt()...");
        }
    }

    namespace InterfaceSegregationBAD
    {
        interface IDataAccess
        {
            void SaveData(DataElement dataElement);
            IList<DataElement> QueryData(string criteria);
            IList<DataElement> GetReportData();
        }

        public abstract class DataAccess : IDataAccess
        {
            public abstract void SaveData(DataElement dataElement);
            public abstract IList<DataElement> QueryData(string criteria);
            public abstract IList<DataElement> GetReportData();
        }

        //BAD: method NOT USED from the FAT interface must throw not implemented interface
        public class ReportDataAccess : DataAccess
        {
            override public void SaveData(DataElement dataElement)
            {
                Console.WriteLine(System.Reflection.MethodBase.GetCurrentMethod().Name);
                throw new NotImplementedException();
            }

            override public IList<DataElement> QueryData(string criteria)
            {
                Console.WriteLine(System.Reflection.MethodBase.GetCurrentMethod().Name);
                throw new NotImplementedException();
            }

            override public IList<DataElement> GetReportData()
            {
                Console.WriteLine(System.Reflection.MethodBase.GetCurrentMethod().Name);

                //IList<DataElement> dataElements = new List<DataElement> { new DataElement() };
                return new List<DataElement> { new DataElement() };
            }
        }
    }

    //BETTER SOLUTION: split the interface, so that, each client has a small one, according to its needs
    namespace InterfaceSegregationOK
    {

        interface IReportDataAccess
        {
            IList<DataElement> GetReportData();
        }

        interface IDataAccess : IReportDataAccess
        {
            void SaveData(DataElement dataElement);
            IList<DataElement> QueryData(string criteria);
        }

        public abstract class DataAccess : IDataAccess
        {
            public abstract void SaveData(DataElement dataElement);
            public abstract IList<DataElement> QueryData(string criteria);
            public abstract IList<DataElement> GetReportData();
        }

        public abstract class ReportDataAccess : IReportDataAccess
        {
            public abstract IList<DataElement> GetReportData();
        }

        //BAD: method NOT USED from the FAT interface must throw not implemented interface
        //no need to implement unnecessary methods anymore
        public class GeneralReportDataAccess : ReportDataAccess
        {
            override public IList<DataElement> GetReportData()
            {
                Console.WriteLine(System.Reflection.MethodBase.GetCurrentMethod().Name);

                //IList<DataElement> dataElements = new List<DataElement> { new DataElement() };
                return new List<DataElement> 
                { 
                    new DataElement(),
                    new DataElement(),
                    new DataElement(),
                    new DataElement()
                };
            }
        }
    }

    //--------------------------------------------------------
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(System.Reflection.MethodBase.GetCurrentMethod().Name);

            Console.WriteLine("__________________________________________________");
            new SingleResponsibilityBAD().CreatePost(new Database(), "SingleResponsibilityBAD");

            Console.WriteLine("__________________________________________________");
            new SingleResponsibilityOK().CreatePost(new Database(), "SingleResponsibilityOK");

            Console.WriteLine("__________________________________________________");
            IPost post1 = new OpenClosePrincipalOK.Post(new Database(), "The First Post");
            post1.CreatePost();

            IPost post2 = new OpenClosePrincipalOK.TagPost(new Database(), "###The First Tag Post");
            post2.CreatePost();

            IPost post3 = new OpenClosePrincipalOK.PostComment(new Database(), "@@@The First Post comment");
            post3.CreatePost();

            Console.WriteLine("__________________________________________________");
            //L — Liskov substitution principle:
            List<IPost> posts = new List<IPost>
            {
                post1,
                post2,
                post3,
                post3,
                post2,
                post1
            };
            new PostHandler().HandlePosts(posts);

            //Interface segregation
            Console.WriteLine("__________________________________________________");
            IReportDataAccess reportDataAccess = new GeneralReportDataAccess();
            IList<DataElement> l = reportDataAccess.GetReportData();
            // or
            //IList<DataElement> l =  new GeneralReportDataAccess().GetReportData();

            foreach (DataElement el in l)
            {
                el.ShowIt();
            }
        }
    }
}
