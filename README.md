## Diamond-Sketch
Sketch is a probabilistic data structure used to record frequencies of items in a multiset. Due to its high e ciency, it has been applied in a variety of fields in computer science, such as data stream processing, natural language processing, network traffic measurement, etc. The key metrics of a sketch are speed, accuracy, and memory usage. Although multiple kinds of sketches have been proposed in the literature, they are not accurate enough, especially for practical datasets which are non-uniformly distributed. We proposed a novel sketch, namely Diamond sketch, which has a significantly higher accuracy than the prior art. The Diamond sketch includes three separate parts: increment part, carry part, and deletion part. All these three parts are composed of atom sketches. The key idea of our Diamond sketch is to dynamically assign an appropriate number of atom sketches to record the frequency of each incoming item, optimizing memory e ciency. Experimental results show that the Diamond sketch outperforms the best of the  ve typical sketches by up to 10.2 times in terms of accuracy. To verify the effectiveness and efficiency of our framework, we applied our framework to four typical sketches.

## About the source codes, dataset and parameters setting

The source code contains the C++ implementation of the CM, CU, C, A sketch and PCM, PCU, PC, PA sketch (using our Pyramid sketch framework). We complete these codes on OS X 10.11.6 and compile successfully using g++ 4.8.4. 

The file `ip_trace.dat` is the subset of one of the encrypted IP traces used in experiments.

## How to run

Suppose you've already cloned the respository and start from the `Codes` directory.

You just need:

	$ make 
	$ ./diamond


## Output format

Our program will print the ARE and AAE of these sketches in `resAAE.dat` and `resARE.dat` respectively.
