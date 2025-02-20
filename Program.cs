// tutorial: https://learnxinyminutes.com/csharp/
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
using System.Configuration;
using System.Security.Policy;
using static Learning.csharp.Program;

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
        public class MyClass
        {
            private int _value;
            private int _otherValue;
            public MyClass(int value, int otherValue)
            {
                _value = value;
                _otherValue = otherValue;
            }
            public MyClass() : this(0, 0) { Console.WriteLine("Initiating MyClass with default parameters..."); }
            public int Value
            { 
                get { Console.WriteLine("Accessing MyClass.Value..."); return _value;  }
                set { Console.WriteLine("Setting MyClass.Value...");  _value = value; }  
            }
            public int OtherValue{ get; set; }
            public override string ToString()
            {
                return $"MyClass {{ {_value}, {_otherValue} }}";
            }
            public bool IsValid { get { return _value > _otherValue; } }
            public int this[int index]
            {
                get { return index == 0 ? _value : _otherValue; }
                set { if (index == 0) _value = value; else _otherValue = value; }
            }

        }
        public static void Classes()
        {
            MyClass ClassInstance = new MyClass(1, 2);
            Console.WriteLine($"ClassInstance is {ClassInstance}");
            ClassInstance.OtherValue = 12;
            Console.WriteLine($"Modified OtherValue to 12: {ClassInstance}");
            ClassInstance.Value = 99;
            Console.WriteLine($"ClassInstance is {ClassInstance}");
            Console.WriteLine($"Printing MyClass.Value using get method {ClassInstance.Value}");
            MyClass ClassInstanceDefault = new MyClass();
            Console.WriteLine($"ClassInstanceDefault is {ClassInstanceDefault}");
            Console.WriteLine($"Is ClassInstanceDefault valid? {ClassInstanceDefault.IsValid}");
            Console.WriteLine($"ClassInstanceDefault index at 0: {ClassInstanceDefault[0]}");
            Console.WriteLine($"ClassInstanceDefault index at 1: {ClassInstanceDefault[1]}");
        }
        //public static void Structs()
        //{
        //}
        public static int SampleRandom()
        {
            return GlobalRandom.Next(0, 100);
        }
        public static int SampleRandom(int min, int max)
        {
            return GlobalRandom.Next(min, max);
        }
        public static char SampleRandom(string Text)
        {
            int textLength = Text.Length;
            int randomIndex = GlobalRandom.Next(0, textLength);
            return Text[randomIndex];
        }
        public static void MethodSignatures()
        {
            Console.WriteLine($"SampleRandom(): {SampleRandom()}");
            Console.WriteLine($"SampleRandom(1,5): {SampleRandom(1,5)}");
            Console.WriteLine($"SampleRandom(\"abcde\"): {SampleRandom("abcde")}");
        }
        public interface IIndexable<TElement>
        {
            TElement this[int index] { get; }
        }
        public class GenericIndexClass<TCollection, TElement> where TCollection : IIndexable<TElement>
        {
            private readonly TCollection Items;
            public TElement GetItemAt(int Where)
            {
                return Items[Where];
            }
            public GenericIndexClass(TCollection items)
            {
                Items = items;
            }
        }
        public static void Generics()
        {
            List<int> listOfInts = new List<int> { 1, 2, 3 };
            var genericIndexClass = new GenericIndexClass<List<int>, int>(listOfInts);
        }
        public static void Yields()
        {
        }
        public static void PassByReference()
        {
        
        }
        public static void Inheritance()
        {
        }
        public static void Composition()
        {
        }
        public static void DependencyInjection()
        {
        }
        public static void Main(string[] args)
        {

            DataStructures();
            Console.WriteLine('\n'+new string('-', 50)+'\n');
            ControlStructures();
            Console.WriteLine('\n'+new string('-', 50)+'\n');
            Typecasting();
            Console.WriteLine('\n'+new string('-', 50)+'\n');
            Classes();
            Console.WriteLine('\n' + new string('-', 50) + '\n');
            MethodSignatures();
        }
    }
}

