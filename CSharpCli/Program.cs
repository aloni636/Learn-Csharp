using System;
using System.Numerics;
using CppCli;  // Ensure this matches the namespace in C++/CLI

// TODO (1): Pass complex data types (arrays, structs, std::vector).
// TODO (2): Handle memory ownership (who allocates/deallocates?).
// TODO (3): Mix native (std::string, std::vector) and managed (String^, List<>) types.
// TODO (4): Call C# from C++/CLI (reverse interop!).
// TODO (5): Optimize performance (minimizing unnecessary GC overhead).

class Program
{
    static void Main()
    {
        CppCliClass interop = new CppCliClass();
        Console.WriteLine($@"Basic data structures from C++/CLI:
  String: {interop.GetString()}
  Solution to the universe: {interop.GetInt()}
  Pi: {interop.GetDouble()}
  Is 42 Positive? {interop.IsPositive(42)}
  Division(5,2): {interop.IntDivision(5, 2)}
");

        string helloWorld = interop.AppendStrings("hello", " world");
        Console.WriteLine($"Appending in native C++: {helloWorld}\n");

        string managedUTF16String = interop.GetUTF16String();
        Console.WriteLine($"Received a UTF16 native std::wstring: {managedUTF16String}\n");

        int[] staticArray = interop.GetFixedArray();
        Console.WriteLine("Static array from native C++: " + String.Join(", ", staticArray));
        interop.ClampIntElements(ref staticArray, 2, 4);
        Console.WriteLine("Clamping inplace in C++: " + String.Join(", ", staticArray) + "\n");

        List<int> dynamicArray = interop.GetDynamicArray(8);
        Console.WriteLine("Dynamic array from C++: " + String.Join(", ", dynamicArray));
        interop.AppendIntToArray(ref dynamicArray, 2);
        Console.WriteLine("Appending inplace in C++: " + String.Join(", ", dynamicArray) + "\n");

        CppCli.ManagedStruct managedStruct = interop.GetStruct();
        Console.WriteLine($"Stack allocated native C++ struct: {interop.StructAsString(managedStruct)}");

        ManagedRandomNumberGenerator mrng = new ManagedRandomNumberGenerator(42, 1, 5);  // TODO: automatically generating seed leads to generate() calls returning 1749605806 and not respecting minmax bounds
        Console.WriteLine($"Generating random number using native C++ class: {mrng.generate()}\n");
    }
}
