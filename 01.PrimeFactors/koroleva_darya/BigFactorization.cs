using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Numerics;
using System.Diagnostics;

namespace ConsoleApp3
{
    static class Program
    {
        static void Main(string[] args)
        {
            StreamReader fin = new StreamReader("C:\\Users\\Daria Koroleva\\Documents\\sharp1n.txt");
            StreamWriter fout = new StreamWriter("C:\\Users\\Daria Koroleva\\Documents\\1234out.txt");

            BigInteger x;

            
            try
            {
                while (!fin.EndOfStream)
                {
                    String s = fin.ReadLine();
                    x = BigInteger.Parse(s); //может возникать "Не удалось выполнить синтаксический анализ значения"

                    Stopwatch timer = new Stopwatch();
                    timer.Start();

                    SortedDictionary<BigInteger, int> div = Fact(x);

                    timer.Stop();


                    if (div.Count() == 0)
                    {
                        fout.Write("+");
                        //fout.Write("+ {0}", x);
                        //Console.Write("+ {0} ", x);
                    }
                    else
                    {
                        fout.Write("-");
                        fout.Write("- {0} = ", x);
                        foreach (KeyValuePair<BigInteger, int> p in div)
                        {
                            fout.Write(" {0}^{1}*", p.Key, p.Value);
                            //Console.Write(" {0}^{1}*", p.Key, p.Value);
                        }
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

        static SortedDictionary<BigInteger, int> Fact(BigInteger x)
        {
            //SortedDictionary<BigInteger, int> div = new SortedDictionary<BigInteger, int>();

            //BigInteger x2 = x;
            //for (BigInteger i = 2; i * i <= x; i++)
            //{
            //    while (x % i == 0)
            //    {
            //        x /= i;

            //        if (!div.ContainsKey(i))
            //        {
            //            div.Add(i, 1);
            //        }
            //        else
            //        {
            //            div[i]++;
            //        }
            //    }
            //}

            //if (x != 1 && x != x2)
            //{
            //    div.Add(x, 1);
            //}

            //return div;

            //НОРМ
            //+1633437 миллисекунд = 22 минуты простое 48112959837082048697
            //+459304 миллисекунд = 7,39 минут (случайное простое 10037721641183543501)
            //-82 миллисекунд (82972060123669301521 =  2400271^1* 4800541^1* 7200811^1)

            BigInteger x2 = x;

            SortedDictionary<BigInteger, int> div = new SortedDictionary<BigInteger, int>();

            if (x == 1)
            {
                div.Add(1, 1);
                return div;
            }

            if (x == 2 || x == 3 || x == 5)
            {
                return div;
            }

            int [] arr235 = new int [] { 2, 3, 5 };

            for (int i = 0; i < 3; i++)
            {
                while (x % arr235[i] == 0)
                {
                    x /= 2;
                    if (!div.ContainsKey(i))
                    {
                        div.Add(arr235[i], 1);
                    }
                    else
                    {
                        div[arr235[i]]++;
                    }
                }
            }


            //-186 (18674341893407349233 =  7^1* 5564401^1* 479434017719^1 НЕВЕРНОЕ РАЗЛОЖЕНИЕ 5564401 = 683 · 8147)
            //РЕШЕНИЕ: ПОМЕНЯТЬ ЦИКЛЫ МЕСТАМИ (ЧТОБЫ ДЕЛИТЬ НА ЧИСЛА ПО ВОЗРОСТАНИЮ)

            int[] arr = new int [] { 1, 7, 11, 13, 17, 19, 23, 29 };
            BigInteger sqrtX = Sqrt(x);
            for (int i = 0; i < 8; i++)
            {
                //заменить на корень для BigInteger (написать?), изменять, когда нашли делитель
                for (BigInteger j = 0; /*(30 * j + arr[i]) * (*/ 30 * j + arr[i] /*)*/ <= sqrtX; j++)
                {

                    BigInteger d = 30 * j + arr[i];
                    if (d == 1) continue;

                    while (x % d == 0)
                    {
                        x /= d;
                        sqrtX = Sqrt(x);

                        if (!div.ContainsKey(d))
                        {
                            div.Add(d, 1);
                        }
                        else
                        {
                            div[d]++;
                        }
                    }
                }


            }

            if (x != 1 && x != x2)
            {
                div.Add(x, 1);
            }

            return div;
        }

        //КОПИПАСТА
        static BigInteger Sqrt(this BigInteger n)
        {
            if (n == 0) return 0;
            if (n > 0)
            {
                int bitLength = Convert.ToInt32(Math.Ceiling(BigInteger.Log(n, 2)));
                BigInteger root = BigInteger.One << (bitLength / 2);

                while (!isSqrt(n, root))
                {
                    root += n / root;
                    root /= 2;
                }

                return root;
            }

            throw new ArithmeticException("NaN");
        }

        static Boolean isSqrt(BigInteger n, BigInteger root)
        {
            BigInteger lowerBound = root * root;
            BigInteger upperBound = (root + 1) * (root + 1);

            return (n >= lowerBound && n < upperBound);
        }

    }



   
}
