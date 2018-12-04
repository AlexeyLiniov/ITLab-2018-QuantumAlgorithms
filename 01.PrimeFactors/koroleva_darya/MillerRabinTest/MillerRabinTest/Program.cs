using System;
using System.IO;
using System.Numerics;
using System.Diagnostics;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MillerRabinTest
{
    class Program
    {
        const int n = 100;
        static void Main(string[] args)
        {
            StreamReader fin = new StreamReader("E:\\Git Projects\\inputs_fact\\composite15n_in.txt");
            StreamWriter fout = new StreamWriter("C:\\Users\\Daria Koroleva\\Documents\\mr_c15out.txt");

            BigInteger x;
            string line;

            try
            {
                while ((line = fin.ReadLine()) != null)
                {

                    x = BigInteger.Parse(line);

                    Stopwatch timer = new Stopwatch();
                    timer.Start();

                    bool b = MillerRabin(x);

                    timer.Stop();

                    if (b)
                    {
                        fout.Write("+");
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
                fout.Write("Число не было прочитано! (формат входного файла: число и перенос строки)");
            }

            fin.Close();
            fout.Close();



        }

        static bool MillerRabin(BigInteger x)
        {
            //1 - составное, 0 - простое
            double d = 1;
            for (int i = 0; i < n; i++)
            {
                
                if (MillerRabinAlgorithm(x))
                {
                    d /= 4;
                }
            }

            if (d < 0.5)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        static bool MillerRabinAlgorithm(BigInteger x)
        {
            if (x == 0 || x == 1)
                return false;
            if (x == 2 || x == 3)
                return true;

            Random rand = new Random();
            BigInteger a = rand.Next() + 1;

            BigInteger pow = x - 1;

            bool lastisone = false;

            while (pow % 2 == 0)
            {
                if (BigInteger.ModPow(a, pow, x) == 1)
                {
                    lastisone = true;
                    if (pow % 2 == 0)
                    {
                        pow /= 2;
                        continue;
                    }
                    else
                    {
                        return true; //степень больше не делится, значит последняя, если последняя 1 и раньше не был сделан вывод, то все единицы и можно вернуть простое
                    }
                }
                else
                {
                    
                    if (/*BigInteger.ModPow(a, pow, x) == -1 ||*/ BigInteger.ModPow(a, pow, x) == x - 1)
                    {
                        if (lastisone)
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
            }


            //для нечетных степеней
            if (BigInteger.ModPow(a, pow, x) == 1 || BigInteger.ModPow(a, pow, x) == x - 1 && lastisone)
            {
                return true;
            }
            else
            {
                return false;
            }

        }
    }
}
