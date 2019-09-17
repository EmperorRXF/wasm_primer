'use strict'

const fs = require('fs');

%NeverOptimizeFunction(isPrime);
%NeverOptimizeFunction(main);

function isPrime(n) {
	if (n <= 1)
		return false;

	let sqrt_n = Math.sqrt(n);

    for (let i = 2; i <= sqrt_n; i++)
		if (n % i == 0)
			return false;

    return true;
}

function main() {
	if (process.argv.length < 4) {
		console.log(`usage: ${process.argv[0]} ${process.argv[1]} nthPrimeNumber groupBy`);
		return;
	}

	let primeCount = 2;
	let maxPrimeCount = process.argv[2];
	let groupBy = process.argv[3];
	let currentPrimeCheck = 3;
	let isPrimeNumber;
	let begin;
	let end;
	let time_spent = 0;

	fs.writeFileSync('output-node.csv', "1,2,0.0\n");

	while (primeCount <= maxPrimeCount) {
		begin = process.hrtime();
		isPrimeNumber = isPrime(currentPrimeCheck);
		end = process.hrtime();
		
		if (isPrimeNumber) {
			time_spent += (end[0] - begin[0]) + ((end[1] - begin[1]) / (1000.0 * 1000.0 * 1000.0));
			
			if (primeCount % groupBy == 0)
			{
				fs.appendFileSync('output-node.csv', `${primeCount},${currentPrimeCheck},${time_spent}\n`);
			}
			
			primeCount++;
		}
		
		currentPrimeCheck += 2;
	}
}

main();