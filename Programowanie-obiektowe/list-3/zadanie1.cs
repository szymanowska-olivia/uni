using System;
using System.Collections.Generic;

abstract class Expression
{
    public abstract int Evaluate(Dictionary<string, int> s);
    public abstract Expression Derivate(string variable);
}

class Const : Expression
{
    private int value;
    public Const(int value) { this.value = value; }
    
    public override int Evaluate(Dictionary<string, int> s)
    {
        return value;
    }
    
    public override Expression Derivate(string variable)
    {
        return new Const(0);
    }
    
    public override string ToString()
    {
        return value.ToString();
    }
}

class Variable : Expression
{
    private string name;
    public Variable(string name) { this.name = name; }
    
    public override int Evaluate(Dictionary<string, int> s)
    {
        if (!s.ContainsKey(name))
        {
        throw new KeyNotFoundException($"Brak wartości w słowniku.");
        }

        return s[name];
    }
    
    public override Expression Derivate(string variable)
    {
        if (name == variable)
        {
            return new Const(1);
        }
        return new Const(0);
    }
    
    public override string ToString()
    {
        return name;
    }
}

class Add : Expression
{
    private Expression left, right;
    
    public Add(Expression left, Expression right)
    {
        this.left = left;
        this.right = right;
    }
    
    public override int Evaluate(Dictionary<string, int> s)
    {
        return left.Evaluate(s) + right.Evaluate(s);
    }
    
    public override Expression Derivate(string variable)
    {
        return new Add(left.Derivate(variable), right.Derivate(variable));
    }
    
    public override string ToString()
    {
        return "(" + left.ToString() + " + " + right.ToString() + ")";
    }
}

class Multiply : Expression
{
    private Expression left, right;
    public Multiply(Expression left, Expression right)
    {
        this.left = left;
        this.right = right;
    }
    
    public override int Evaluate(Dictionary<string, int> s)
    {
        return left.Evaluate(s) * right.Evaluate(s);
    }
    
    public override Expression Derivate(string variable)
    {
        return new Add(new Multiply(left.Derivate(variable), right), new Multiply(left, right.Derivate(variable)));
    }
    
    public override string ToString()
    {
        return "(" + left.ToString() + " * " + right.ToString() + ")";
    }
}

class Application
{
    static void Main()
    {
        Expression expr = new Add(new Const(4), new Variable("x"));
        Expression expr2 = new Multiply(new Variable("y"), new Variable("z"));
        Dictionary<string, int> s = new Dictionary<string, int> { { "x", 3 },{ "y", 10},{"z", 6}};
        
        
        Console.WriteLine(expr);
        Console.WriteLine("dla x=3: " + expr.Evaluate(s));
        
        Expression pochodna = expr.Derivate("x");
        
        Console.WriteLine("Pochodna: " + expr.Derivate("x"));
        Console.WriteLine("Pochodna: " + pochodna.Evaluate(s));
        
        Console.WriteLine(expr2);
        Console.WriteLine("dla x=3: " + expr2.Evaluate(s));
        Expression pochodna2 = expr.Derivate("y");
        Console.WriteLine("Pochodna: " + expr.Derivate("y"));
        Console.WriteLine("Pochodna: " + pochodna2.Evaluate(s));
        

        
    }
}
