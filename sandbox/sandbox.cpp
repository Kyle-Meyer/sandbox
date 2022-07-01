// sandbox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
#include <vector>
#include <chrono>
#include <map>
#include <math.h>
#include "string.h"
#include <unordered_map>
using namespace std;

/*

void printArr(vector<int> arr, int n);

void inserstionSort(vector<int>& arr, int n)
{
	int i, key, j = 0;
	i = 1;
	//iterate through the list
	while (i < n)
	{
		key = arr[i];
		int j = i - 1;
		//keep swapping elements stop when we either hit the end of the list or we encounter an element that is greater than our current key
		while(j >= 0 && arr[j] > key)
		{
			//bubble out the greater elements
			swap(arr[j + 1], arr[j]);
			j--;
		}
		//set our key into its new place
		arr[j + 1] = key;
		i++;
	}
}

void selectionSort(vector<int>& arr, int n)
{
	//iterate through the list
	int temp;
	for (int i = 0; i < arr.size()-1; i++)
	{
		int min = i;
		//scan for smallest element in unordered sublist
		for (int j = i+1; j < arr.size(); j++)
		{
			if (arr[j] < arr[min])
			{
				min = j;
			}
		}
		//if our min was never updated, swap
		if(arr[i] != arr[min])
			swap(arr[i], arr[min]);
	}
}
void merge(vector<int>& arr , int left, int mid, int right)
{
	//create new arrays
	vector<int> temp;

	//specify our indexes
	int indexLeft = left;
	int indexRight = mid + 1;
	
	//start merging our arrays together
	while (indexLeft <= mid && indexRight <= right)
	{
		//merge our element if the left array is smaller than the right
		if (arr[indexLeft] <= arr[indexRight])
		{
			temp.push_back(arr[indexLeft]);
			indexLeft++;
		}
		//if thats not the case, then the right must be smaller, and will be merged instead
		else
		{
			temp.push_back(arr[indexRight]);
			indexRight++;
		}
	
	}
	
	//should any elements exist in the left array, copy them over as is
	while (indexLeft <= mid)
	{
		temp.push_back(arr[indexLeft]);
		indexLeft++;
	}

	//should any elements exist in the right array, copy them over as is
	while (indexRight <= right)
	{
		temp.push_back(arr[indexRight]);
		indexRight++;
	}
	//correct our original array, by copying the temp array
	for (int i = left; i <= right; i++)
	{
		arr[i] = temp[i - left];
	}
}
void mergeSort(vector<int>& arr, int begin, int end)
{

	if (begin < end)
	{
		int mid = (begin + end) / 2;
		//iterate left
		mergeSort(arr, begin, mid);
		//iterate right
		mergeSort(arr, mid + 1, end);
		//merge in our array's
		merge(arr, begin, mid, end);
	}
}

int partition(vector<int>& arr, int start, int end)
{
	//our last element is our pivot
	int pivot = end;
	//this is needed to keep track of what to pivot
	int indexTemp = start;
	for (int i = start; i < end; i++)
	{
		//shift all of our lower values to the left of the pivot
		if (arr[i] < arr[pivot])
		{
			swap(arr[i], arr[indexTemp]);
			indexTemp++;
		}
	}
	//lastly, swap the pivot and the last greater than element
	swap(arr[indexTemp], arr[pivot]);
	//return our index so we now where to divide the array
	return indexTemp;
}

void quickSort(vector<int>& arr, int start, int end)
{
	if (end <= start)
		return;
	//get our partition
	int part = partition(arr, start, end);
	//traverse left and sort
	quickSort(arr, start, part - 1);
	//traverse right and sort
	quickSort(arr, part + 1, end);

}
void printArr(vector<int> arr, int n)
{
	
	cout << "current array:	 " << endl;
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " , ";
	}
	cout << endl;
}

void runTest(vector<int>& arr, int size)
{
	//this is to measure clock cycles
	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;
	
	//this is to create copies of our vector for each test case, otherwise it would try to sort an already sorted array
	vector<int> copy1 = arr;
	vector<int> copy2 = arr;
	vector<int> copy3 = arr;
	vector<int> copy4 = arr;
	
	//insertion sort measure
	auto t1 = high_resolution_clock::now();
	inserstionSort(copy1, size);
	auto t2 = high_resolution_clock::now();
	duration<double, std::milli> ms_double = t2 - t1;
	cout << " ***** insertion sort on size " << copy1.size() << " took " << ms_double.count() << " miliseconds" << endl;
	//printArr(copy1, size);
	//selection sort measure
	t1 = high_resolution_clock::now();
	selectionSort(copy2, size);
	t2 = high_resolution_clock::now();
	ms_double = t2 - t1;
	cout << " ***** selection sort on size " << copy2.size() << " took " << ms_double.count() << " miliseconds" << endl;
	//printArr(copy2, size);
	//merge sort measure
	t1 = high_resolution_clock::now();
	mergeSort(copy3, 0, size - 1);	
	t2 = high_resolution_clock::now();
	ms_double = t2 - t1;
	cout << " ***** merge sort on size " << copy3.size() << " took " << ms_double.count() << " miliseconds" << endl;
	//printArr(copy3, size);
	//quick sort measure
	t1 = high_resolution_clock::now();
	mergeSort(copy4, 0, size - 1);
	t2 = high_resolution_clock::now();
	ms_double = t2 - t1;
	cout << " ***** quick sort on size " << copy4.size() << " took " << ms_double.count() << " miliseconds" << endl;
	//printArr(copy4, size);
	
	//printArr(copy1, size);
	
	

}
int main()
{


	random_device rnd;
	mt19937 mersenne_engine{ rnd() };  // Generates random integers
	uniform_int_distribution<int> dist{ 1, 52 };
	auto gen = [&dist, &mersenne_engine]() {
		return dist(mersenne_engine);
	};
	vector<int> test = { 8,4,2,1,2,7,5,3,24 };
	vector<int> arr(10000);
	vector<int> arr1(20000);
	vector<int> arr2(30000);
	vector<int> arr3(40000);
	vector<int> arr4(50000);
	vector<int> arr5(60000);
	vector<int> arr6(70000);
	vector<int> arr7(80000);
	vector<int> arr8(90000);
	vector<int> arr9(100000);
	

	cout << "filling arrays... \n";
	generate(begin(arr), end(arr), gen);
	generate(begin(arr1), end(arr1), gen);
	generate(begin(arr2), end(arr2), gen);
	generate(begin(arr3), end(arr3), gen);
	generate(begin(arr4), end(arr4), gen);
	generate(begin(arr5), end(arr5), gen);
	generate(begin(arr6), end(arr6), gen);
	generate(begin(arr7), end(arr7), gen);
	generate(begin(arr8), end(arr8), gen);
	generate(begin(arr9), end(arr9), gen);

	cout << "calling test battery on array1, size 10000" << endl;
	runTest(arr, arr.size());
	cout << "calling test battery on array2, size 20000" << endl;
	runTest(arr1, arr1.size());
	cout << "calling test battery on array3, size 30000" << endl;
	runTest(arr2, arr2.size());
	cout << "calling test battery on array4, size 40000" << endl;
	runTest(arr3, arr3.size());
	cout << "calling test battery on array5, size 50000" << endl;
	runTest(arr4, arr4.size());
	cout << "calling test battery on array6, size 60000" << endl;
	runTest(arr5, arr5.size());
	cout << "calling test battery on array7, size 70000" << endl;
	runTest(arr6, arr6.size());
	cout << "calling test battery on array8, size 80000" << endl;
	runTest(arr7, arr7.size());
	cout << "calling test battery on array9, size 90000" << endl;
	runTest(arr8, arr8.size());
	cout << "calling test battery on array10, size 100000" << endl;
	runTest(arr9, arr9.size());
}
*/


//paper 2

/*

int findMax(vector<int> arr, int size)
{
	int finalEnt;
	bool oddFlag = false;
	if (size == 1)
		return arr[0];
	vector<int> newArr;
	if (size % 2 == 1)
	{
		finalEnt = arr[size - 1];
		arr.pop_back();
		size = size - 1;
		oddFlag = true;
		
	}
	for (int i = 0; i < size; i += 2)
	{
		int temp = std::max(arr[i], arr[i + 1]);
		newArr.push_back(temp);
		
	}
	//for odd even entries
	if (oddFlag == true)
	{
		int newArrLast = newArr[newArr.size() - 1];
		newArr[newArr.size()-1] = std::max(newArrLast, finalEnt);
	}
	int newMax = findMax(newArr, size / 2);
	return newMax;
}

#define vr 4
#define INF 99999
void printSolution(int dist[][vr])
{
	cout << "The following matrix shows the shortest "
		"distances"
		" between every pair of vertices \n";
	for (int i = 0; i < vr; i++) {
		for (int j = 0; j < vr; j++) {
			if (dist[i][j] == INF)
				cout << "INF"
				<< "     ";
			else
				cout << dist[i][j] << "     ";
		}
		cout << endl;
	}
}
void floydWarshall(int graph[][vr])
{

	int dist[vr][vr], i, j, k;


	for (i = 0; i < vr; i++)
		for (j = 0; j < vr; j++)
			dist[i][j] = graph[i][j];


	for (k = 0; k < vr; k++) {
		// Pick all vertices as source one by one
		for (i = 0; i < vr; i++) {
			// Pick all vertices as destination for the
			// above picked source
			for (j = 0; j < vr; j++) {
				// If vertex k is on the shortest path from
				// i to j, then update the value of
				// dist[i][j]
				if (dist[i][j] > (dist[i][k] + dist[k][j])
					&& (dist[k][j] != INF
						&& dist[i][k] != INF))
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}

	// Print the shortest distance matrix
	printSolution(dist);
	
}



int TSP(int grph[][vr], int start) // implement traveling Salesman Problem. 
{
	floydWarshall(grph);
	vector<int> ver; //
	for (int i = 0; i < vr; i++)
		if (i != start)
		{
			ver.push_back(i);
		}
	int m_p = INT_MAX; // store minimum weight of a graph
	vector<int> finalPath;
	//generate permutations of our set
	while (next_permutation(ver.begin(), ver.end())) 
	{
		//our current path
		int cur_pth = 0;

		int nextNode = start;
		cout << endl;
		for (int i = 0; i < ver.size(); i++) 
		{
			//traverse the path
			cur_pth += grph[nextNode][ver[i]];
			//store the last node we were on
			nextNode = ver[i];
		}
		//make sure we head back to our start
		cur_pth += grph[nextNode][start];
		//update our minimum path
		if (cur_pth < m_p)
		{
			m_p = cur_pth;
			finalPath = ver;
		}
	
	}
	cout << "final Decided Path: " << start+1 <<  " -> ";
	for (int i = 0; i < finalPath.size(); i++)
	{
		if (i != 0 && i != finalPath.size())
			cout << " -> ";
		cout << " " << finalPath[i] + 1 <<  " ";
	}
	cout << endl;
	return m_p;
}
int main()
{
	vector<int> arr1 = {1, 10, 11, 5, 22, 9, 8, 42, 0, 2};
	cout << "max was: " << findMax(arr1, arr1.size()) << endl;
	int graph[][vr] = { { 0, 10, 15, 20 },
					   { 10, 0, 35, 25 },
					   { 15, 35, 0, 30 },
					   { 20, 25, 30, 0 } };
	int p = 0;
	cout << "\n The result is: " << TSP(graph, p) << endl;
	return 0;
}*/





//paper 3

/*
void printArray(vector<char> arr, int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}
void permute(string a, int l, int r)
{
	// Base case
	if (l == r)
		cout << a << endl;
	else
	{
		// Permutations made
		for (int i = l; i <= r; i++)
		{

			// Swapping done
			swap(a[l], a[i]);

			// Recursion called
			permute(a, l + 1, r);

			//backtrack
			swap(a[l], a[i]);
		}
	}
}
vector<vector<char>> total;
vector<vector<char>> permuteCustom(vector<char> arr, int index,
	vector<char> subarr, vector<vector<char>> allSubs)
{
	// Print the subsequence when reach
   // the leaf of recursion tree
	if (index == arr.size())
	{
	
		if (!subarr.empty())
		{
			
			//total.push_back(subarr);
			allSubs.push_back(subarr);
		}
	}
	else
	{
		// Subsequence without including
		// the element at current index
		permuteCustom(arr, index + 1, subarr, allSubs);

		subarr.push_back(arr[index]);

		// Subsequence including the element
		// at current index
		permuteCustom(arr, index + 1, subarr, allSubs);
	}
	return allSubs;

}

int maxSubsequenceSubstring(vector<char> x, vector<char> y,
	int n, int m)
{
	int dp[9][9];

	// Initialize the dp[][] to 0. 
	for (int i = 0; i <= m; i++)
		for (int j = 0; j <= n; j++)
		{
			dp[i][j] = 0;
		}
	// Calculating value for each element. 
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {

			// If alphabet of string X and Y are 
			// equal make dp[i][j] = 1 + dp[i-1][j-1] 
			if (x[j - 1] == y[i - 1])
				dp[i][j] = 1 + dp[i - 1][j - 1];

			// Else copy the previous value in the 
			// row i.e dp[i-1][j-1] 
			else
				dp[i][j] = dp[i][j - 1];
		}
	}
	for (int i = 0; i < n; i++)
	{
		
		
		for (int j = 0; j < m; j++)
		{
			
			cout << x[i] << " , " << y[j] << " : " << dp[i][j] << " " << endl;
		}
	

	}
	// Finding the maximum length. 
	int ans = 0;
	for (int i = 1; i <= m; i++)
		ans = max(ans, dp[i][n]);

	return ans;
}
*/

//two sum hash solution
//complexity: O(n), but requires more space, however each lookup will now cost O(1) which is pooper fast

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		//again we can create a simple hash using the map function, if you want a refresher on maps see: https://www.udacity.com/blog/2020/03/c-maps-explained.html
		map<int, int> map;
		//store our pairs
		vector<int> pairs;
		for (int i = 0; i < nums.size(); i++)
		{
			int comp = target - nums[i];
			/*the idea here is simple, we search for the complement to whatever
			current element we are on, as the complement to
			the target will mean that the current element + said complement = target
			if we find the complement in our hash table, we know the solution exists and can
			therefore push the answer, for maps in c++ the .end() returns the iterator for end of the hash
			we MUST use a hash here to prevent a backwards O(n^2) complexity */
			if (map.find(comp) != map.end())
			{
				pairs.push_back(map.find(comp)->second);
				pairs.push_back(i);
				//little debug
				cout << "just pushed back hash second pointer: " << map.find(comp)->second << " on iteration: " << i << " will now break operation" << endl;
				break;
			}
			//no matter what we will add the current entry of the original list we are on into the hash table
			map.insert(pair<int, int>(nums[i], i));
		}
		return pairs;
	}
};


//K distant problem solution
//algorithmic solution, we can start by searching for the key throughout the list, we can then perform an O(n) search throughout the list to find pivots matching the returned indeces from the exponential search

//function to find all instances from a list


vector<int> findItems(vector<int>& nums, int target)
{
	vector<int> found;
	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] == target)
			found.push_back(i);
	}
	return found;
}

vector<int> findKDistantIndices(vector<int>& nums, int key, int k)
{
	vector<int> ans;
	int size = nums.size();

	int i = 0, j = 0;

	while (j < size) {
		if (nums[j] == key) {
			if (abs(i - j) <= k && i < size) 
			{
				ans.push_back(i);
				i++;
			}
			else 
			{
				i > j ? j++ : i++;
			}
		}
		else 
		{
			j++;
		}
	}

	return ans;
}

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	int carry = 0;
	//start a new list
	ListNode* dummy = new ListNode(-1);
	ListNode* head = dummy;

	//while not at the end of either list, or we have an unhandeled carry
	while (l1 || l2 || carry) {
		//add our first entry
		if (l1) 
			carry += l1->val;
		//add our second entry
		if (l2) 
			carry += l2->val;
		//generate our next node, mod it by 10 to get the remainder
		head->next = new ListNode(carry % 10);
		//book keeping on carry
		carry /= 10;
		//traverse
		head = head->next;
		if (l1) l1 = l1->next;
		if (l2) l2 = l2->next;
	}
	head = dummy->next;
	delete dummy;
	return head;
}


//longest substring without repeating characters

int lengthOfLongestSubstring(string s) {
	vector<int> chars(128);
	int left = 0;
	int right = 0;
	int res = 0;
	//start counting to the right
	while (right < s.length()) {
		char r = s[right];
		//add the character to our visited table
		chars[r]++;
		//if we found a repeating entry begin the closing of the window
		while (chars[r] > 1) {
			//initialize a character
			char l = s[left];
			//remove it from the table
			chars[l]--;
			//move up
			left++;

		}
		//finish out the loop when we have no more repeating characters take the max of the window size
		res = max(res, right - left + 1);
		//step forward
		right++;
	}

	return res;
}


//string to integer (atoi)


int stringToInteger(string str)
{
	int sign = 1, base = 0, i = 0;
	//bleed white spaces
	while (str[i] == ' ') { i++; }
	if (str[i] == '-' || str[i] == '+') {
		//whacky ass setting of negative flag, and incrementing at the same time, for a weird case of +-12
		sign = 1 - 2 * (str[i++] == '-');
	}
	//start adding our digits
	while (str[i] >= '0' && str[i] <= '9') {
		//clamp our result to the 32 bit integer range, we have to handle it in one of 2 cases
		//1: we are already outisde of the 32 bit integer range (the first conditional)
		//2: we are still inside the 32 bit integer range until the last possible digit (the second conditional)
		if (base > INT_MAX / 10 || (base == INT_MAX / 10 && str[i] - '0' > 7)) {
			if (sign == 1) return INT_MAX;
			else return INT_MIN;
		}
		base = 10 * base + (str[i++] - '0');
	}
	return base * sign;
}


//container with most water
int maxAreaWater(vector<int>& height)
{
	//flush the retardation of leetcode
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//declare essentials
	int left = 0, right = height.size() - 1, maxer = 0;
	while (left < right)
	{
		//calculate the area
		maxer = max(maxer, (min(height[right], height[left]) * (right - left)));
		//traverse either left or right
		if (height[left] <= height[right])
			left++;
		else
			right--;
	}

	return maxer;
}


string intToRoman(int num)
{
	string ret;
	vector<string> ones = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
	vector<string> tens = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
	vector<string> hunds = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
	vector<string> thous = { "", "M", "MM", "MMM" };

	ret.append(thous[num / 1000]);
	ret.append(hunds[num % 1000 / 100]);
	ret.append(tens[num % 100 / 10]);
	ret.append(ones[num % 10]);
	return ret;

}

int romanToInt(string str)
{
	int ret = 0, i = 0;
	bool done = false;
	while(!done)
	{
		switch (str[i])
		{
		case 'M' :
			ret += 1000;
			break;
		case 'D':
			ret += 500;
			break;
		case 'C':
			if (str[i + 1] && str[i + 1] == 'D')
			{
				ret += 400;
				i++;
			}
			else if (str[i + 1] && str[i + 1] == 'M')
			{
				ret += 900;
				i++;
			}
			else
				ret += 100;
			break;
		case 'L':
			ret += 50;
			break;
		case 'X':
			if (str[i + 1] && str[i + 1] == 'L')
			{
				ret += 40;
				i++;
			}
			else if (str[i + 1] && str[i + 1] == 'C')
			{
				ret += 90;
				i++;
			}
			else
				ret += 10;
			break;
		case 'V':
			ret += 5;
			break;
		case 'I':
			if (str[i + 1] && str[i + 1] == 'V')
			{
				ret += 4;
				i++;
			}
			else if (str[i + 1] && str[i + 1] == 'X')
			{
				ret += 9;
				i++;
			}
			else
				ret += 1;
			break;
		default:
			done = true;
			break;
		}
		i++;
	}
	return ret;
}

vector<vector<int>> threeSum(vector<int> arr)
{
	//the answer
	vector<vector<int>> sol;
	//sort our array
	std::sort(arr.begin(), arr.end());
	//start iterating
	for (int i = 0; i < arr.size(); i++)
	{
		//create our pivots
		int l = i + 1, r = arr.size() - 1;
		//analyze based on our pivots skip repeating but also make sure we can check behind us
		if (i == 0 || arr[i - 1] != arr[i])
		{
			//now its essentiall the sum problem
			while (l < r)
			{
				int sum = arr[i] + arr[l] + arr[r];
				//if we are lower than 0, our left pivot must be too small, hence iterate it
				if (sum < 0)
				{
					l++;
				}
				//if we are above zero, decrement right pivot
				else if (sum > 0)
					r--;
				//if if we have a match, push it back
				else
				{
					vector<int> temp = { arr[i] , arr[l], arr[r] };
					sol.push_back(temp);
					l++;
					r--;
					while (l < r && arr[l] == arr[l - 1])
						l++;
				}
			}
		}
	}

	//return out
	return sol;


}
int main()
{

	/*Solution sol;
	vector<int>nums = { 1,4,3,6,5,8 };
	cout << "original list : ";
	for (int i = 0; i < nums.size(); i++)
	{
		cout << nums[i] << " , ";
	}
	cout << endl;
	vector<int>pair = sol.twoSum(nums, 14);
	cout << "pair indices are : " << pair[0] << " " << pair[1] << endl;*/
	//std::vector<int> vec{ 3,4,9,1,3,9,5 };
	//vector<int> solutions = findKDistantIndices(vec, 9, 1);
	/*std::vector<int> vec{2,2,2,2,2};
	vector<int> solutions = findKDistantIndices(vec, 2, 2);
	for (int i = 0; i < solutions.size(); i++)
	{
		cout << solutions[i] << ",";
	}
	cout << endl;
	*/
	//string test = "abcabcbb";
	//cout << lengthOfLongestSubstring(test) << endl;
	
	
	/*
	string tester = "+-12";
	cout << "runnin: " << tester << " : " << endl;
	cout << stringToInteger(tester) << endl;
	tester = "+12";
	cout << "runnin: " << tester << " : " << endl;
	cout << stringToInteger(tester) << endl;

	tester = "-+12";
	cout << "runnin: " << tester << " : " << endl;
	cout << stringToInteger(tester) << endl;

	tester = "-12";
	cout << "runnin: " << tester << " : " << endl;
	cout << stringToInteger(tester) << endl;
	*/

	//water area driver
	/*
	vector<int> arr1 = { 1, 8, 6, 2, 5, 4, 8, 3, 7 };
	cout << maxAreaWater(arr1) << endl;
	*/

	//roman to int Driver
	/*
	cout << intToRoman(24) << endl;
	cout << romanToInt("CMXLII") << endl;
	*/


	vector<int> test = { -1,0,1,2,-1,-4 };
	vector<vector<int>> solution = threeSum(test);
	for (int i = 0; i < solution.size(); i++)
	{
		cout << "entry: " << i << " : ";
		for (int j = 0; j < solution[i].size(); j++)
		{
			cout << " " << solution[i][j] << ", ";
		}
		cout << endl;
	}
	return 0;
}