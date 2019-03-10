using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Numerics;



namespace RSA
{
	class Program
    {
        static void Main(string[] args)
        {
            RSA rsa = new RSA();
            string s = "abcef123";

            string enc = rsa.Encrypt(s);
            Console.WriteLine(enc);

            Console.ReadKey();

            string dec = rsa.Decrypt(enc);
            Console.WriteLine(dec);

			Console.ReadKey();

		}
    }

    class RSA
    {

		public BigInteger n;
        public BigInteger e;
        BigInteger d;

		public RSA()
		{
			BigInteger p = Functions.GeneratePrime();

			BigInteger q;


			do
			{
				q = Functions.GeneratePrime();
			} while (q == p);

            n = BigInteger.Multiply(p, q);

            BigInteger m = (p - 1) * (q - 1);

            d = Functions.RelativelyPrime(ref m);

            e = Functions.Inverse(d, m);

			//n = 954529;
			//d = 977;
			//e = 951601;
        }

        public string Encrypt (string s)
        {
            int slen = s.Length;

            string enc = "";

            for (int i = 0; i < slen; ++i)
            {
                enc += BigInteger.ModPow(s[i], e, n);
                enc += ' ';
            }

            return enc;
        }

        public string Decrypt(string s)
        {
            int slen = s.Length;

            string dec = "";

            string[] numbers = s.Split(' ');

            for (int i = 0; i < numbers.Length; i++)
            {
				//numbers[i] = numbers[i].Remove(numbers[i].Length - 1, 1); ;

				//Console.WriteLine(numbers[i]);

				BigInteger numb = 0;
				if (BigInteger.TryParse(numbers[i], out numb))
				{
					BigInteger a1, a2, a3, a4;
					a1 = numb;
					a2 = d;
					a3 = n;
					a4 = BigInteger.ModPow(a1, a2, a3);
					dec += (char) (BigInteger.ModPow(numb, d, n)); //ОШИБКА ТУТЬ, НАВЕРНОЕ

				}

            }
            
            return dec;
        }

        


    }

    static class Functions
    {
        public static BigInteger Inverse(BigInteger a, BigInteger m)
        {
            if (BigInteger.GreatestCommonDivisor(a, m) != 1)
            {
                return 0; //нет обратного
            }

            BigInteger[] u = new BigInteger[] { a, 1 };
            BigInteger[] v = new BigInteger[] { m, 0 };

            while (v[0] != 0)
            {
                BigInteger[] t = new BigInteger[] { u[0] % v[0], u[1] - (u[0] / v[0]) * v[1] };
                u = v;
                v = t;
            }

            if (u[1] > 0)
            {
                return u[1] % m;
            }
            else
            {
                return m + u[1];
            }

        }

        public static BigInteger GeneratePrime()
        {
			const int SIZEOF_PRIME_BITS = 10;

			Random rand = new Random();
            int bits = SIZEOF_PRIME_BITS;
            BigInteger pow = BigInteger.Pow(2, bits - 1);
            BigInteger numb;

            do
            {
                numb = pow;

                numb |= (BigInteger)1;
                for (int i = 1; i < bits - 1; ++i)
                {
                    if (rand.Next() % 2 == 1)
                        numb |= (BigInteger)1 << i;
                }
            } while (!Is_Prime.MillerRabin(numb));

            return numb;
        }

        public static BigInteger RelativelyPrime (ref BigInteger bg)
        {
            BigInteger rp;
            do
            {
                rp = Functions.GeneratePrime();
            } while (BigInteger.GreatestCommonDivisor(bg, rp) != 1);

            return rp;
        }

    }


    public static class Is_Prime
    {
        const int n = 100;

        public static bool MillerRabin(BigInteger x)
        {
            //1 - составное, 0 - простое
            double probably_composite = 1;
            for (int i = 0; i < n; i++)
            {

                if (MillerRabinAlgorithm(x))
                {
                    probably_composite /= 4;
                }
                else
                {
                    return false;

                    //для возврата вероятности
                    //return 1;
                }

            }

            return true;

            //для возврата вероятности
            //return probably_composite;
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
