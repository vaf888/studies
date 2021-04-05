using System;
using System.Threading.Tasks;

namespace Async
{
    class TestAsync
    {
        static async Task<int> GetDataFromNetworkAsync()
        {
            // simulates a call to a network
            // VIP: await DOES NOT BLOCK - just "returns back" to scheduler,
            // then, later, on task is done, processing will continue in next line
            // var res = 42 !
            // IF we do not add await - the thread will BLOCK, not allowing other processing
            // to run in parallel
            // AWAIT IS SIMILAR TO YIELD (go back to scheculer & continue after task finished)
            await Task.Delay(150);
            var res = 42;

            return res;
        }

        public async void  test001()
        {
            // must have the await - otherwise will block - await frees the thread to the scheculer
            Console.WriteLine(">>>>>calling await GetDataFromNetworkAsync()...");
            var res = await GetDataFromNetworkAsync();
            Console.WriteLine(">>>>>Back from GetDataFromNetworkAsync()");
            Console.WriteLine("res={0}", res);
        }

        //--- using a lambda ---
        Func<Task<int>> GetDataFromNetworkViaLambdaAsync = async () =>
        {
            //150 ms
            //await Task.Delay(150);
            //or
            await Task.Delay(TimeSpan.FromMilliseconds(150));
            var res = 42;

            return res;
        };

        public async void test002()
        {
            // must have the await - otherwise will block - await frees the thread to the scheculer
            Console.WriteLine(">>>>>calling await GetDataFromNetworkViaLambdaAsync()...");
            var res = await GetDataFromNetworkViaLambdaAsync();
            Console.WriteLine(">>>>>Back from GetDataFromNetworkViaLambdaAsync()");
            Console.WriteLine("res={0}", res);
        }
    }

    //----------------------------------------------------------
    class Program
    {
        static void Main(string[] args)
        {

            Console.WriteLine("______________________________________");
            new TestAsync().test001();

            //running this code below in parallel with test001() + GetDataFromNetworkAsync()
            for (int i = 0; i < 10; ++i)
                Console.WriteLine(">>>>>Still in main-1 !!!");


            Console.WriteLine("______________________________________");
            new TestAsync().test002();

            //running this code below in parallel with test001() + GetDataFromNetworkAsync()
            for (int i = 0; i < 10; ++i)
                Console.WriteLine(">>>>>Still in main-2 !!!");

            Console.ReadKey();
            
        }
    }
}
