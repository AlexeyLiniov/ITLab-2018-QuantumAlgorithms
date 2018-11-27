using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Numerics;
using System.Diagnostics;

namespace ConsoleApp1
{
    class Program
    {
        const int k = 100;
        static void Main(string[] args)
        {
            StreamReader fin = new StreamReader("E:\\Git Projects\\inputs_fact\\composite15_in.txt");
            StreamWriter fout = new StreamWriter("C:\\Users\\Daria Koroleva\\Documents\\sharp1.txt");

            BigInteger x;
            string line;

            try
            {
                while ((line = fin.ReadLine()) != null)
                {

                    x = BigInteger.Parse(line);

                    Stopwatch timer = new Stopwatch();
                    timer.Start();

                    bool b = Ferma(x);

                    timer.Stop();

                    if (b)
                    {
                        fout.Write("+ {0} ", x);
                    }
                    else
                    {
                        fout.Write("-");
                    }
                    fout.WriteLine(timer.ElapsedMilliseconds); //нужно в микросекундах
                }
            }
            catch
            {

            }

            fin.Close();
            fout.Close();



        }


        static bool Ferma(BigInteger x)
        {
            if (x == 2)
                return true;
            Random rand = new Random();
            for (int i = 0; i < k; i++)
            {
                BigInteger a = (rand.Next() % (x - 2)) + 2;
                Console.WriteLine(a);
                if (GCD(a, x) != 1)
                    return false;
                if (Pows(a, x - 1, x) != 1)
                    return false;
            }
            return true;
        }
        static BigInteger GCD(BigInteger a, BigInteger b) //алгоритм Евклида (НОД)
        {
            if (b == 0)
                return a;
            return GCD(b, a % b);
        }

        static BigInteger Mul(BigInteger a, BigInteger b, BigInteger m)
        {
            if (b == 1)
                return a;
            if (b % 2 == 0)
            {
                BigInteger t = Mul(a, b / 2, m);
                return (2 * t) % m;
            }
            return (Mul(a, b - 1, m) + a) % m;
        }

        static BigInteger Pows(BigInteger a, BigInteger b, BigInteger m)
        {
            if (b == 0)
                return 1;
            if (b % 2 == 0)
            {
                BigInteger t = Pows(a, b / 2, m);
                return Mul(t, t, m) % m;
            }
            return (Mul(Pows(a, b - 1, m), a, m)) % m;
        }
    }
}
