// See https://aka.ms/new-console-template for more information
using System;
using System.Collections.Generic;
using System.Dynamic;
using System.Linq;
using System.Net;
using System.Threading.Tasks;
using System.IO;

using System.Data.Entity;

namespace Learning.csharp
{
    public class Program
    {
        public static void Syntax()
        {
            Console.WriteLine("Hello, World!");
            int oneInt = 10;
            double twoAndAHalf = 2.5;
            bool boolean = false;
            byte byteVariable = 255;  // (0 <= byte <= 255)
            sbyte sbyteVariable = 127;  // (-128 <= sbyte <= 127)
            sbyte oneSbyte = 1;
            byte oneByte = 1;
            // TODO: Learn about string concatenation

            Console.WriteLine(
                "Int: " + oneInt +
                "\nDouble: " + twoAndAHalf +
                "\nBoolean: " + boolean +
                "\nByte: " + byteVariable +
                "\nSbyte: " + sbyteVariable +
                "\nByteOverflow?: " + (byteVariable + oneByte) +
                "\nSbyteOverflow?: " + (sbyteVariable + oneSbyte)
            );

            Console.WriteLine(new string('-', 5));

            int[] intArray = Enumerable.Range(0, 10).ToArray();
            Console.WriteLine("Array element: " + intArray[0]);
            //Console.WriteLine("".Join(',', intArray));
            List<int> ints = new List<int> { 1, 2, 3 };
            Dictionary<string, int> dictionary = new Dictionary<string, int> {
                {"hello", 1 }
            };
            Console.WriteLine("Dictionary element: " + dictionary["hello"]);
            //Console.WriteLine("Dictionary unavailable element: " + dictionary["world"]);  // throws error
        }
        public static void Main(string[] args)
        {
            Syntax();
        }
    }
}

