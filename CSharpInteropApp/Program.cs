using System;
using System.Runtime.InteropServices;

class Program
{
    [DllImport("CppInteropLib.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int AddNumbers(int a, int b);

    static void Main()
    {
        int result = AddNumbers(5, 10);
        Console.WriteLine($"Result from C++: {result}");
    }
}