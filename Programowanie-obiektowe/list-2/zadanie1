using System;

    class IntStream {
        protected int liczba = 0;

        public int next() {
            liczba++;
            if (eos()) return -1;
            return liczba - 1;
        }

        public bool eos() {
            return liczba == int.MaxValue;
        }

        public void reset() {
            liczba = 0;
        }
    }

    class FibStream : IntStream {
        private int prev = 0;
        private int curr = 1;

        public new int next() {
            int pom = prev;
            prev = curr;
            curr = curr + pom;
            return pom;
        }

        public new bool eos() {
            return curr < 0; 
        }

        public new void reset() {
            prev = 0;
            curr = 1;
        }
    }

    class RandomStream : IntStream {
        private Random random = new Random();

        public new int next() {
            return random.Next();
        }

        public new bool eos() {
            return false; 
        }
    }

    class RandomWordStream {
        private FibStream fibStream = new FibStream();
        private RandomStream randomStream = new RandomStream();
        
        public string next() {
            int length = fibStream.next();
            string word = "";
            for (int i = 0; i < length; i++) word += (char)('a' + (randomStream.next() % 26));
            return word;
        }

        public void reset() {
            fibStream.reset();
        }
    }

    class Application {
        static void Main() {
            Console.WriteLine("IntStream:");
            IntStream intStream = new IntStream();
            for(int i=0;i<7;i++) Console.WriteLine(intStream.next());
            intStream.reset();
            for(int i=0;i<3;i++) Console.WriteLine(intStream.next());
    
            Console.WriteLine("\nFibStream:");
            FibStream fibStream = new FibStream();
            for(int i=0;i<7;i++) Console.WriteLine(fibStream.next());
            fibStream.reset();
            for(int i=0;i<3;i++) Console.WriteLine(fibStream.next());

            Console.WriteLine("\nRandomStream:");
            RandomStream randomStream = new RandomStream();
            for(int i=0;i<10;i++) Console.WriteLine(randomStream.next());
            
            Console.WriteLine("\nRandomWordStream:");
            RandomWordStream randomWordStream = new RandomWordStream();
            fibStream.reset();
            for(int i=0;i<7;i++) Console.WriteLine(randomWordStream.next()); 
            randomWordStream.reset();
            for(int i=0;i<5;i++) Console.WriteLine(randomWordStream.next());
            
        }
    }
