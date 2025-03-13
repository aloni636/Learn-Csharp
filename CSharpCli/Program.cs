using System;
using CppCli;  // Ensure this matches the namespace in C++/CLI

class Program
{
    static void Main()
    {
        CppCliClass obj = new CppCliClass();
        Console.WriteLine(obj.GetMessage());
    }
}
