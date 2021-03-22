using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace ConsoleApplication1
{
    class Program
    {
        [DllImport("Win32Project1.dll", ExactSpelling = false)]
        public static extern int TestFunction();

        [DllImport("Win32Project1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Sum(int a, int b);

        [DllImport("Win32Project1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr QueryString();

        static void Main(string[] args)
        {
            int d = TestFunction();
            Console.WriteLine(d);
            int r = Sum(33, 6);
            Console.WriteLine(r);
            IntPtr queryString = QueryString();
            string sql = Marshal.PtrToStringAnsi(queryString);
            Console.WriteLine(sql);
            Console.ReadKey();
        }
    }
}
