const fs = require('fs');
function sieveOfEratosthenes(n = 100, p = false) {
    /*
     * Args:
     * - n (int) sieve to n
     * - p (bool) whether to print our not
     */
    console.log("start")
    let primes1 = [];
    let primes2 = [];
    let primes3 = [];
    let primes4 = [];
    let primes5 = [];
    function getValue(l){
        if (l <= n/5){
            return primes1[l];
        }
        else if(l <= 2*n/5){
            return primes2[l-n/5-1];
        }
        else if(l <= 3*n/5){
            return primes3[l-2*n/5-1];
        }
        else if(l <= 4*n/5){
            return primes4[l-3*n/5-1];
        }
        else{
            return primes5[l-4*n/5-1];
        }
    }
    console.log("filling array")
    primes1 = Array(n/5 + 1).fill(true);  // Assume all numbers in array are prime
    console.log("1 done")
    primes3 = Array(n/5).fill(true);  // Assume all numbers in array are prime
    console.log("2 done")
    primes3 = Array(n/5).fill(true);  // Assume all numbers in array are prime
    console.log("3 done")
    primes4 = Array(n/5).fill(true);  // Assume all numbers in array are prime
    console.log("4 done")
    primes5 = Array(n/5).fill(true);  // Assume all numbers in array are prime
    console.log("Array filling done!")
    primes1[0] = primes1[1] = false;         // Except for 0 and 1
    k = 0;
    console.log("starting main loop")
    for (let i = 2; i <= Math.sqrt(n); i++) {
        if (getValue(i)) {
            for (let j = i * i; j <= n; j += i) {
                if (getValue(j)){k++;}         
                if (j <= n/5){
                    primes1[j] = false;
                }
                else if(j <= 2*n/5){
                    primes2[j-n/5-1] = false;
                }
                else if(j <= 3*n/5){
                    primes3[j-2*n/5-1] = false;
                }
                else if(j <= 4*n/5){
                    primes4[j-3*n/5-1] = false;
                }
                else{
                    primes5[j-4*n/5-1] = false;
                }
                if (k%20000 == 0){
                    process.stdout.write(`\r${k}`);
                }
            }
        }
    }
    console.log("main loop over")
    let primes = [];
    console.log("final list")
    primes.push(primes1.reduce((acc, isPrime, index) => {
        if (isPrime) acc.push(index);
        return acc;
    }, []));
    console.log("1 done")
    primes.push(primes2.reduce((acc, isPrime, index) => {
        if (isPrime) acc.push(index + n/5 + 1);
        return acc;
    }, []));
    console.log("2 done")
    primes.push(primes3.reduce((acc, isPrime, index) => {
        if (isPrime) acc.push(index + 2*n/5 + 1);
        return acc;
    }, []));
    console.log("3 done")
    primes.push(primes4.reduce((acc, isPrime, index) => {
        if (isPrime) acc.push(index + 3*n/5 + 1);
        return acc;
    }, []));
    console.log("4 done")
    primes.push(primes5.reduce((acc, isPrime, index) => {
        if (isPrime) acc.push(index + 4*n/5 + 1);
        return acc;
    }, []));
    console.log("5 done")
    return primes;
}
if (require.main === module) {
    const readline = require('readline').createInterface({
        input: process.stdin,
        output: process.stdout
    });
    readline.question("print? ", (prinInput) => {
        const prin = prinInput.toLowerCase() === 'true';
        readline.question("int ", (iInput) => {
            const i = parseInt(iInput);
            const res = sieveOfEratosthenes(i, prin);
            fs.writeFileSync("/Users/ed/Downloads/past school stuff/python projects/primes.txt", JSON.stringify(res));
            readline.close();
        });
    });
}
