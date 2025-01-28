// See https://aka.ms/new-console-template for more information
using System;
using System.Collections.Generic;
using System.Dynamic;
using System.Linq;
using System.Net;
using System.Threading.Tasks;
using System.IO;
using System.Linq;  // Language-Integrated Query, allows SQL like expressions on linq enabled data structures
using System.Data.Entity;
using System.Security.Cryptography.X509Certificates;

namespace Learning.csharp
{
    public class Program
    {
        private static readonly Random GlobalRandom = new Random();
        public static void DataStructures()

        {
            Console.WriteLine("Hello, World!");
            int oneInt = 10;
            double twoAndAHalf = 2.5;
            bool boolean = false;
            byte byteVariable = byte.MaxValue;  // (0 <= byte <= 255)
            sbyte sbyteVariable = sbyte.MaxValue;  // (-128 <= sbyte <= 127)
            sbyte oneSbyte = 1;
            byte oneByte = 1;
            // TODO: Learn about string concatenation
            unchecked
            {
                Console.WriteLine(
                    "Int: " + oneInt +
                    "\nDouble: " + twoAndAHalf +
                    "\nBoolean: " + boolean +
                    "\nByte: " + byteVariable +
                    "\nSbyte: " + sbyteVariable +
                    "\nByteOverflow?: " + (byteVariable + oneByte) +  // arithmetic is done on minimum element size of 32 bit / ints: https://stackoverflow.com/a/941665
                    "\nSbyteOverflow?: " + (sbyteVariable + oneSbyte)
                );
            }

            Console.WriteLine(new string('-', 5));  //  String reptation 

            int[] intArray = Enumerable.Range(0, 10).ToArray();  // Create array of range
            Console.WriteLine($"Array elements: {string.Join(',', intArray)}");  // String interpolation with expressions (from version 6.0)

            // Lists, Dictionaries, Sets, Stacks and Queues

            Dictionary<string, int> dictionary = new Dictionary<string, int> {
                {"hello", 1 }
            };
            // Merge dictionaries with graceful handling of duplicate keys
            Dictionary<string, int> dictionary2 = new Dictionary<string, int> {
                {"hello", 2 },
                {"world", 2 }
            };
            foreach (var item in dictionary2)
            {
                dictionary[item.Key] = item.Value;
            }

            // Join dictionary elements into list
            Console.WriteLine("\nDictionary: { " + string.Join(", ", dictionary.Select(kvp => $"{kvp.Key}: {kvp.Value}"))+ "}");  // kvp = key value pair
            Console.WriteLine("The dictionary again: { " + dictionary.Select(kvp => $"{kvp.Key}: {kvp.Value}").Aggregate((cur, next) => $"{cur}, {next}")+" }");
            Console.WriteLine("Dictionary element: " + dictionary["hello"]);
            Console.WriteLine($"Default int value: {default(int)}");
            Console.WriteLine("Unavailable element defaults to value's default value: " + (dictionary.GetValueOrDefault("foo").ToString()));
            
            List<int> intList = new List<int> { 1, 2, 3 }; // Can also be initialized using square brackets [1,2,3]
            // Appending elements to list
            intList.Add(4);
            intList.AddRange([-1,-2,-3]); 
            intList.AddRange(new List<int> { -1, -2, -3 }); 

            Console.WriteLine("intList: [ " + string.Join(", ", intList.Select((i)=>i.ToString()))+" ]");
            HashSet<int> hashSet = new HashSet<int> { 1, 2, 3, 11 };
            HashSet<int> setRange = new HashSet<int>(Enumerable.Range(0, 10));
            Console.WriteLine("\nhashSet union: { "+string.Join(", ", hashSet.Union(setRange).Select((i) => i.ToString()))+" }");
            Console.WriteLine("hashSet difference: { "+string.Join(", ", hashSet.Except(setRange).Select((i) => i.ToString()))+" }");
        }
        public static void ControlStructures()
        {
            foreach (int i in Enumerable.Range(0, 10))
            {
                if (i % 2 == 0)
                {
                    Console.WriteLine("Even: " + i);
                }
                else
                {
                    Console.WriteLine("Odd: " + i);
                }
            }
        }
        public static void Typecasting()
        {
            Console.WriteLine("Provide an integer to parse:");
            string userInput = Console.ReadLine() ?? "";
            if (int.TryParse(userInput, out int tryInt))  // TODO: Learn how to use out keyword in custom methods
            {
                Console.WriteLine("Parsed int: " + tryInt);
                string tryIntAsString = tryInt.ToString();
                Console.WriteLine("Parsed int Hex: " + tryInt.ToString("X"));  // X is a format identifier, see: https://learn.microsoft.com/en-us/dotnet/api/system.int32.tostring?view=net-9.0
                long tryIntAsLong = (long)tryInt;
                byte[] intBytes = BitConverter.GetBytes(tryInt);
                byte[] longBytes = BitConverter.GetBytes(tryIntAsLong);
                Console.WriteLine("Parsed int bytes: " + BitConverter.ToString(intBytes));
                Console.WriteLine("Parsed int as long bytes: " + BitConverter.ToString(longBytes));
            }
            else
            {
                Console.WriteLine("Failed to parse int");
            }
        }
        public static void Functions()
        {
            // default and optional parameters, keywords args, variable amount of arguments
            int MyMethod(int positional, int optional=4, int? optionalNull = null, params int[] numbers)
            {
                return positional + optional + (optionalNull ?? 0) + numbers.Sum();
            }
            Console.WriteLine("MyMethod with positional, keyword, and variadic args: " + MyMethod(1, optionalNull:2, optional:3, numbers: [4, 5]));
            bool OutMethod(out int outParam)
            {
                int randInt = GlobalRandom.Next(0,2);
                outParam = randInt;
                return (randInt == 0);
            }
            if (OutMethod(out int outParam))
            {
                Console.WriteLine("OutMethod returned true with outParam: " + outParam);
            }
            else
            {
                Console.WriteLine("OutMethod returned false with outParam: " + outParam);
            }
        }
        public static void Main(string[] args)
        {

            DataStructures();
            Console.WriteLine('\n'+new string('-', 50)+'\n');
            ControlStructures();
            Console.WriteLine('\n'+new string('-', 50)+'\n');
            Typecasting();
        }
    }
}

