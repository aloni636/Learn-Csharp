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
            if (int.TryParse(userInput, out int tryInt))
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
        public class GenericIndexClass<TCollection, TElement> where TCollection : IReadOnlyList<TElement>
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
            Console.WriteLine("GenericIndexClass at index 1 with List<int>: " + genericIndexClass.GetItemAt(1));
        }
        public static void Yields()
        {
            static IEnumerable<int> FactorialGenerator(int n)
            {
                int result = 1;
                for (int i = 1; i <= n; i++)
                {
                    result *= i;
                    yield return result;
                }
            }
            int factorialLimit = 5;
            Console.WriteLine($"Factorial till {factorialLimit}:");
            foreach (var (factorial, index) in FactorialGenerator(factorialLimit).Select((v,i) => (v,i)))
            {
                Console.WriteLine($"{index}! = {factorial}");
            }
        }
        public struct LargeStruct
        {
            public int Field1;
            public int Field2;
            public int Field3;
            public int Field4;
            public int Field5;
            public int Field6;
            public int Field7;
            public int Field8;
            public int Field9;
            public int Field10;

            public Span<int> AsSpan() { return new Span<int>(new int[] { 
                Field1,
                Field2,
                Field3,
                Field4,
                Field5,
                Field6,
                Field7,
                Field8,
                Field9,
                Field10 
            }); }
        }
        public static void PassByReference()
        {
            // out methods are actually pass by reference, and modify the out variable inplace
            // in methods are pass by reference, but as readonly
            // ref methods are pass by reference, and can modify the ref variable inplace
            void increment(ref int value)
            {
                value++;
            }
            int value = 0;
            Console.WriteLine($"Value before increment: {value}");
            increment(ref value);
            Console.WriteLine($"Value after increment {value}");
            void printLargeStruct(in LargeStruct structInput)
            {
                int i = 1;
                foreach (int structItem in structInput.AsSpan())
                {
                    Console.WriteLine($"Struct.Field{i}: {structItem}");
                    i++;
                }
            }
            LargeStruct largeStruct = new LargeStruct
            {
                Field1 = 1*3,
                Field2 = 2*3,
                Field3 = 3*3,
                Field4 = 4*3,
                Field5 = 5*3,
                Field6 = 6*3,
                Field7 = 7*3,
                Field8 = 8*3,
                Field9 = 9*3,
                Field10 = 10*3 
            };
            printLargeStruct(largeStruct);
        }
        public class Animal
        {
            public virtual void Eat() { Console.WriteLine("Animal is eating!"); }  // virtual marks the method as overridable by inheriting classes
        }
        public class Dog : Animal
        {
            public void Bark() { Console.WriteLine("Dog is barking!"); }
            public override void Eat() { Console.WriteLine("Dog is eating!"); }
        }
        public class VectorizedList<T> : List<T> where T : notnull
        {
            // Inheritance cannot transfer construction methods , so we need to define them again
            public VectorizedList() : base() { }
            public VectorizedList(IEnumerable<T> collection) : base(collection) { }
            public VectorizedList(int capacity) : base(capacity) { }
            public static VectorizedList<T> operator +(VectorizedList<T> list, T item)
            {
                VectorizedList<T> newList = new VectorizedList<T>(list);
                for (int i = 0; i < list.Count; i++)
                {
                    newList[i] += (dynamic)item;
                }
                return newList;
            }
            public static VectorizedList<T> operator -(VectorizedList<T> list, T item)
            {
                VectorizedList<T> newList = new VectorizedList<T>(list);
                for (int i = 0; i < list.Count; i++)
                {
                    newList[i] -= (dynamic)item;
                }
                return newList;
            }
            public static VectorizedList<T> operator *(VectorizedList<T> list, T item)
            {
                VectorizedList<T> newList = new VectorizedList<T>(list);
                for (int i = 0; i < list.Count; i++)
                {
                    newList[i] *= (dynamic)item;
                }
                return newList;
            }
            public static VectorizedList<T> operator /(VectorizedList<T> list, T item)
            {
                VectorizedList<T> newList = new VectorizedList<T>(list);
                for (int i = 0; i < list.Count; i++)
                {
                    newList[i] /= (dynamic)item;
                }
                return newList;
            }
        }
        public static void Inheritance()
        {
            Console.WriteLine("Initiating animals...");
            Animal animal = new Animal();
            Dog dog = new Dog();
            animal.Eat();
            dog.Eat();
            VectorizedList<float> vectorizedInts = new VectorizedList<float> { 1, 2, 3 };
            Console.WriteLine("VectorizedInts: " + string.Join(", ", vectorizedInts));
            VectorizedList<float> newVectorizedInts = vectorizedInts + 1;
            Console.WriteLine("VectorizedInts after addition (unchanged, immutable addition): " + string.Join(", ", vectorizedInts));
            Console.WriteLine("newVectorizedInts after addition: " + string.Join(", ", newVectorizedInts));
            Console.WriteLine("newVectorizedInts after math expression: " + string.Join(", ", ((newVectorizedInts*2)+5)/3));
        }
        public static void Composition()
        {
        }
        public static void DependencyInjection()
        {
        }
        public static void RunWithDivider(int dividerSize, params Action[] actions)
        {
            foreach (Action action in actions)
            {
                action();
                Console.WriteLine('\n' + new string('-', dividerSize) + '\n');
            }
        }
        public static void RunWithDivider(params Action[] actions) { RunWithDivider(Console.WindowWidth, actions); }

        public static void Main(string[] args)
        {
            List<int> list = [ 1, 2, 3 ];

            RunWithDivider(
                DataStructures,
                ControlStructures,
                Typecasting,
                Classes,
                MethodSignatures,
                Generics,
                Yields,
                PassByReference,
                Inheritance
            );

        }
    }
}

