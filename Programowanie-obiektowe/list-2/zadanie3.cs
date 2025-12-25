using System;
using System.Collections.Generic;
using System.Linq;

class LazyIntList
{
    protected List<int> numbers = new List<int>();

    public int Element(int i)
    {
        while (numbers.Count <= i) numbers.Add(numbers.Count);
        return numbers[i];
    }

    public int Size()
    {
        return numbers.Count;
    }
}

class LazyPrimeList : LazyIntList
{
    public new int Element(int i)
    {
        while (numbers.Count <= i) numbers.Add(NextPrime());
        return numbers[i];
    }

    private int NextPrime()
    {
        int liczba = numbers.Count > 0 ? numbers[numbers.Count - 1] + 1 : 2;
        while (!IsPrime(liczba)) liczba++;
        return liczba;
    }

    private bool IsPrime(int n)
    {
        if (n < 2) return false;
        for (int i = 2; i * i <= n; i++) if (n % i == 0) return false;
        return true;
    }
}

class Program
{
    static void Main()
    {
        Console.WriteLine("LazyIntList:");
        LazyIntList list = new LazyIntList();
        Console.WriteLine(list.Element(40)); 
        Console.WriteLine(list.Size());
        Console.WriteLine(list.Element(38)); 
        Console.WriteLine("size:");
        Console.WriteLine(list.Size()); 
        
        Console.WriteLine("LazyPrimeList:");

        LazyPrimeList primeList = new LazyPrimeList();
        for(int i=1;i<=12;i++) Console.WriteLine(primeList.Element(i)); 
        Console.WriteLine("size:");
        Console.WriteLine(primeList.Size());
    }
}
