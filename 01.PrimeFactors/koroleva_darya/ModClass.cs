using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;
using System.IO;

namespace ModClass
{
    class Program
    {
        static void Main(string[] args)
        {
            BigInteger a, m;
            a = BigInteger.Parse(Console.ReadLine());
            m = BigInteger.Parse(Console.ReadLine());

            Console.WriteLine(ModFunctions.Inverse (a, m) );
            //Console.WriteLine(ModFunctions.Mul(a, a, m));

            Console.ReadKey();

        }
    }

    static class ModFunctions
    {
        public static BigInteger Inverse(BigInteger a, BigInteger m)
        {
            if (GCD(a, m) != 1)
            {
                return 0; //нет обратного
            }

            BigInteger[] u = new BigInteger [] { a, 1 };
            BigInteger[] v = new BigInteger[] { m, 0 };

            while (v[0] != 0)
            {
                BigInteger[] t = new BigInteger[] { u[0] % v[0], u[1] - (u[0] / v[0]) * v[1] };
                //BigInteger[] t = new BigInteger[] { u[0] % v[0], u[1] - ModFunctions.Mul( (u[0]/v[0]), v[1], m) };
                u = v;
                v = t;
            }

            return u[1] % m;

        }

        public static BigInteger Sum(BigInteger a, BigInteger b, BigInteger m)
        {
            return (a + b) % m;
        }

        public static BigInteger Sub(BigInteger a, BigInteger b, BigInteger m)
        {
            return (a - b) % m; 
        }


        public static BigInteger Mul(BigInteger a, BigInteger b, BigInteger m)
        {
            if (b == 1)
                return a % m;
            if (b % 2 == 0)
            {
                BigInteger t = Mul(a, b / 2, m);
                return (2 * t) % m;
            }
            return (Mul(a, b - 1, m) + a) % m;
        }

        static BigInteger Pows(BigInteger a, BigInteger b, BigInteger m)
        {
            //библиотечная реализация
            //BigInteger.ModPow(a, b, c);

            if (b == 0)
                return 1;
            if (b % 2 == 0)
            {
                BigInteger t = Pows(a, b / 2, m);
                return Mul(t, t, m) % m;
            }
            return (Mul(Pows(a, b - 1, m), a, m)) % m;
        }

        static BigInteger GCD(BigInteger a, BigInteger b) //НОД
        {
            //библиотечная реализация
            //return BigInteger.GreatestCommonDivisor(a, b);

            if (b == 0)
                return a;
            return GCD(b, a % b);
        }


    }
}
