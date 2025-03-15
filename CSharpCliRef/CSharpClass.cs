using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpNamespace
{
    //public delegate void CachedRecursiveFactorialCallback(int factorial);
    public class CSharpClass
    {
        public void PrintMessage(string message)
        {
            Console.WriteLine($"[C#] (from C++): \"{message}\"");
        }
        readonly private Dictionary<int, int> factorialCache = [];
        public int CachedRecursiveFactorial(int factorial)
        {
            if (factorial<2) { return 1; }
            int previousFactorial;

            if (this.factorialCache.ContainsKey(factorial)) {
                previousFactorial = factorialCache[factorial - 1];
            }
            else
            {
                previousFactorial = CachedRecursiveFactorial(factorial - 1);
                factorialCache[factorial - 1] = previousFactorial;
            }
            return factorial * previousFactorial;
        }
    }
}
