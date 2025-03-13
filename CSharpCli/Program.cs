using System;
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
  Solution to the universe: {interop.GetString()}
  Pi: {interop.GetDouble()}
  Is 42 Positive? {interop.IsPositive(42)}
  Division(5,2): {interop.IntDivision(5, 2)}
");
        string helloWorld = interop.AppendStrings("hello", " world");
        Console.WriteLine($"Appending in native C++: {helloWorld}");
    }
}
