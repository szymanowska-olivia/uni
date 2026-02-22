function fib(n: number): number {
  if (n <= 1) return n;
  return fib(n - 1) + fib(n - 2);
}

function memoize<F extends (...args: any[]) => any>(fn: F): F {
  const mem = new Map<string, ReturnType<F>>();
  return ((...args: Parameters<F>) => {
    const key = JSON.stringify(args);
    if (mem.has(key)) return mem.get(key)!;
    const res = fn(...args);
    mem.set(key, res);
    return res;
  }) as F;
}

const fibMemo = memoize(fib);
console.log(fibMemo(40));