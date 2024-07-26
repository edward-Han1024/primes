/*
 * Copyright 2024 Edward Han
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
const fs = require('fs');
function sieveOfEratosthenes(n = 100) {
    /*
     * Args:
     * - n (int) sieve to n
     */
    console.log("start");
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
    console.log("filling array");
    primes1 = Array(n/5 + 1).fill(true);  // Assume all numbers in array are prime
    console.log("1 done");
    primes2 = Array(n/5).fill(true);  // Assume all numbers in array are prime
    console.log("2 done");
    primes3 = Array(n/5).fill(true);  // Assume all numbers in array are prime
    console.log("3 done");
    primes4 = Array(n/5).fill(true);  // Assume all numbers in array are prime
    console.log("4 done");
    primes5 = Array(n/5).fill(true);  // Assume all numbers in array are prime
    console.log("Array filling done!");
    primes1[0] = primes1[1] = false;         // Except for 0 and 1
    k = 0;
    console.log("starting main loop");
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
    console.log("\nmain loop over");
    let primes = [];
    console.log("final list");
    primes.push(primes1.reduce((acc, isPrime, index) => {
        if (isPrime) acc.push(index);
        return acc;
    }, []));
    console.log("1 done");
    primes.push(primes2.reduce((acc, isPrime, index) => {
        if (isPrime) acc.push(index + n/5 + 1);
        return acc;
    }, []));
    console.log("2 done");
    primes.push(primes3.reduce((acc, isPrime, index) => {
        if (isPrime) acc.push(index + 2*n/5 + 1);
        return acc;
    }, []));
    console.log("3 done");
    primes.push(primes4.reduce((acc, isPrime, index) => {
        if (isPrime) acc.push(index + 3*n/5 + 1);
        return acc;
    }, []));
    console.log("4 done");
    primes.push(primes5.reduce((acc, isPrime, index) => {
        if (isPrime) acc.push(index + 4*n/5 + 1);
        return acc;
    }, []));
    console.log("5 done")
    return primes;
}
const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});
readline.question("int ", (iInput) => {
    const i = parseInt(iInput);
    const res = sieveOfEratosthenes(i);
    console.log("storing files");
    fs.writeFileSync("./primes/primes1.txt", JSON.stringify(res[0]));
    console.log("1 done");
    fs.writeFileSync("./primes/primes2.txt", JSON.stringify(res[1]));
    console.log("2 done");
    fs.writeFileSync("./primes/primes3.txt", JSON.stringify(res[2]));
    console.log("3 done");
    fs.writeFileSync("./primes/primes4.txt", JSON.stringify(res[3]));
    console.log("4 done");
    fs.writeFileSync("./primes/primes5.txt", JSON.stringify(res[4]));
    console.log("all done closing...");
    readline.close();
});
