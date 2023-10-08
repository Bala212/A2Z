Pattern:
If asked number of subarrays then atmost vala
exactly(K) = atMost(K) - atMost(K-1)
If asked longest subarray then variable length sliding window
        while(j<n){
            if(nums[j]==0){
                k--;
            }
            while(i<=j && k<0){
                if(nums[i]==0){
                    k++;
                }
                i++;
            }
            ans = max(ans,j-i+1);
            j++;
       }
------------------------------------------------------------------------------------------------------- 
Sliding Window
Window Sliding Technique is a computational technique that aims to reduce the use of nested loops and replace it with a single loop, 
thereby reducing the time complexity.

This technique shows how a nested for loop in some problems can be converted 
to a single for loop to reduce the time complexity.
Sum nikalte raho, jaise condition fail ho, while loop laga kar piche se nikalte raho,
firse jab condition meet ho dubara sum nikalte raho. Think it as a snake eating
maximum of sum amount of food only. Whenever it exceed sum, we remove the
food from snake by back side( left pointer)

Two types->
1) Fixed size: We have given k, and perform some operations on that k size subarray.
2) Variable size: We have given some condition, maximize or minimize, and we are asked to find the maximum or minimum
size of subarray. Here we have to find the size of sliding window.


Patterns:
A) Fixed size
---------------------------------------------------------------------------------------------------------------
A) Fixed size:
Note:
1) Window is represented by left and right pointer.
2) Window size -> right - left + 1.
3) Loop till right < n.
4) if and else if is mandotory, we cannot use if in both conditions.
5) Ek window size ko hit karo, aur fir use manitain krte raho.
6) Slide the window vale step mein, left nikalna important hein, ye step dhyaan se karna padega, question nusar tarika alag alag hein!!

Identification->
1) Array|Subarray|K|Longest|Smallest|Count
2) String|Substring|Longest|Count|Smallest

Basic template->
 while(right<n){
    //Add number/element pointed by right pointer
    if( right - left +1 < k) right++; // Expand window
    else if( right - left +1 ==k){   // We got window of size k
	// 1) calculations to get the answer on given conditions
	// 2) slide the window (left++ an right++); left element is removed here(calculations of left are removed)
              and right element is added upside when loop starts.
    }
 }

Questions:
1) Max Sum Subarray of size K ( Maximum among sum of all subarrays of size k)
https://practice.geeksforgeeks.org/problems/max-sum-subarray-of-size-k5313/1

    long maximumSumSubarray(int k, vector<int> &Arr , int N){
        long n = Arr.size();
        long left = 0,right = 0, sum = 0, ans = 0;
        while(right<n){
            // Add right element into sum
            sum += Arr[right];
            
            // Get the current window size
            int window_size = right - left + 1;
            
            // If window size is less than k, increase the window by moving
            // right ahead
            if(window_size < k){
                right++;
            }
            
            // If window_size == k, maximize the sum and to maintain this k size window
	    // remove left element from window and add right element(added up) to execute 
	    // on to the next window!!
            if(window_size == k){
                ans = max(sum, ans);
                sum -= Arr[left];
                left ++;
                right++;
            }
        }
        
        return ans;
    }
    // TC - O(N)
    // SC - O(1)

	OR

    long maximumSumSubarray(int k, vector<int> &arr , int n){
        long long maxsum = 0, sum = 0;
        for(int i=0; i<k; i++){
            sum+=arr[i];
        }
        maxsum = max(maxsum,sum);
        for(int i=k; i<n; i++){
            sum-=arr[i-k];
            sum+=arr[i];
            maxsum = max(maxsum,sum);
        }
        return maxsum;
    }
    // TC - O(N)
    // SC - O(1)
-------------------------------------------------------------------------
2) First negative integer in every window of size k
https://practice.geeksforgeeks.org/problems/first-negative-integer-in-every-window-of-size-k3345/1

vector<long long> printFirstNegativeInteger(long long int A[], long long int n, long long int k) {
    deque<long long> dq;
    
    int left = 0,right = 0;
    vector<long long> ans;
    
    while(right<n){
        // Add negative number index in deque to keep track of negative elements
        if(A[right] < 0) dq.push_back(right);
        
        // If window size is less than K, move window ahead
        if(right-left+1 < k){
            right++;
        }
        // If window size is equal to K, do calculations and slide the window
        else if(right-left+1 == k){
            //1) Calculations on answer!!
            // If deque is empty, mean this window has no negative elements so push 0 in ans
            if(dq.empty()) ans.push_back(0);
            // deque is not empty, add front indexed element in ans, as it will be the first
            // negative element in current window
            else{
                ans.push_back(A[dq.front()]);
            }
            
            // 2) Slide the window
            // Remove the index(if we are inserting indexes in deque) of negative element present in front of deque
            // if it is the left index of current window
            if(!dq.empty() && left == dq.front()) dq.pop_front();
            // slide window, by moving left and right pointer ahead by 1
            left++;
            right++;
        }
    }
    
    return ans;
 }
    // TC - O(N)
    // SC - O(N)
----------------------------------------------------------------------------------------------------------------------------------
3) Anagrams pattern (fixed size window only)

a) Count Occurences of Anagrams
https://practice.geeksforgeeks.org/problems/count-occurences-of-anagrams5839/1
https://www.youtube.com/watch?v=MW4lJ8Y0xXk&list=PL_z_8CaSLPWeM8BDJmIYDaoQ5zuwyxnfj&index=5
See video from 35 minmutes

int search(string pat, string txt)
{
    int n = txt.size();

    // Window will be of size which smaller string has
    int k = pat.size();

    unordered_map<char, int> m;
    // Store occurrences of pattern in map
    for (auto &ch : pat)
    {
        m[ch]++;
    }

    // this will store distinct characters of txt
    int count = m.size();

    int left = 0, right = 0, ans = 0;

    // We will slide on txt!!!
    while (right < n)
    {
        // If traversing character is present in map, that means it is the part of pattern
        if (m.find(txt[right]) != m.end())
        {
            // reduce the frequency of that character in map
            m[txt[right]]--;

            // if frequency of currentr character becomes 0, that means all occurrences
            // of that character matches, so reduce the count of distinct characters
            if (m[txt[right]] == 0)
                count--;
        }

        // window is small!!
        if (right - left + 1 < k)
            right++;

        // We reach the window size
        else if (right - left + 1 == k)
        {
            // 1) Calculations of answer
            // If count becomes zero, that means we got a window who reduces all
            // occurrences of pattern, count 0 represents all distinct char's are matched
            // We got one window of anagram, increase the ans
            if (count == 0)
                ans++;

            // 2) Slide the window
            // As we reduce the count of characters of pattern while sliding
            // So now to slide/process next window, we should put back the character
            // pointed by left poniter into map again but only if it was already present.
            // Also, we did one thing we decremented count variable whenever we reduce all
            // occurences of a character. Now, while sliding window ahead, we will increment
            // count by 1 when we see that frequency of character goes 1 after pushing into map,
            // i.e. it occurs just now it means it is one of the distinct character.
            if (m.find(txt[left]) != m.end())
            {
                m[txt[left]]++;
                if (m[txt[left]] == 1)
                    count++;
            }
            // move window ahead
            left++;
            right++;
        }
    }

    // return the no. of anagrams
    return ans;
}
	// T.C -> O(N)
	// S.C -> O(26) 
----------------------------------------------
b)  Find All Anagrams in a String
All code is same, in this question we have to give the starting indexes of all the anagrams. For that
instead of doing ans++, declare a vector ans, when we are doing ans++, instead push the starting index of the window i.e. left pointer!!
   vector<int> findAnagrams(string s, string p) {
        int n = s.size();
	    
	    // Window will be of size which smaller string has
	    int k = p.size();
	    
	    unordered_map<char, int> m;
	   // Store occurrences of pattern in map
	    for(auto &ch:p){
	        m[ch]++;
	    }
	    
	   // this will store distinct characters of s
	   int count = m.size();
	    
	    int left = 0, right = 0;
        vector<int> ans;
	    
	   // We will slide on s!!!
	    while(right<n){
	       // If traversing character is present in map, that means it is the part of pattern
	        if(m.find(s[right]) != m.end()){
	           // reduce the frequency of that character in map
	            m[s[right]]--;
	            
	           // if frequency of currentr character becomes 0, that means all occurrences
	           // of that character matches, so reduce the count of distinct characters
	            if(m[s[right]] == 0) count --;
	        }
	        
	       // window is small!!
	        if(right - left +1 < k) right++;
	        
	       // We reach the window size
	        else if(right - left + 1 == k){
	           // 1) Calculations of answer
	           // If count becomes zero, that means we got a window who reduces all
	           // occurrences of pattern, count 0 represents all distinct char's are matched
	           //We got one window of anagram, so push the starting index of window i.e. left
	           if(count == 0) ans.push_back(left);
	           
	           // 2) Slide the window
	           // As we reduce the count of characters of pattern while sliding
	           // So now to slide/process next window, we should put back the character
	           // pointed by left poniter into map again but only if it was already present.
	           // Also, we did one thing we decremented count variable whenever we reduce all 
	           // occurences of a character. Now, while sliding window ahead, we will increment 
	           // count by 1 when we see that frequency of character goes 1 after pushing into
               // map, i.e. it occurs just now it means it is one of the distinct character.
	           if(m.find(s[left]) != m.end()){
	               m[s[left]] ++;
	               if(m[s[left]] == 1) count++;
	           }
	           //move window ahead
	           left++;
	           right++;
	        }
	    }
	    
	   // return the starting indexes of all anagrams
	    return ans;
    }
-------------------------------------------------------------------------------------------------------------------------------------------------
4) Sliding Window Maximum
https://leetcode.com/problems/sliding-window-maximum/
https://www.youtube.com/watch?v=xFJXtB5vSmM&list=PL_z_8CaSLPWeM8BDJmIYDaoQ5zuwyxnfj&index=6
See this video from 36 minutes, to get idea in short.

    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans;
        // We wre using deque bcoz, here we want to deal with entire window of size k
        // i.e. to fetch maximum among k window size, for that we need to also pop
        // some elements from back as well, which are smaller than incoming.
        // And to store the maximums for next window.
        int left = 0, right = 0;
        deque<int> dq;
        while(right<n){
            // nums[right] se jitne smaller elements present hein queue mein, unko pop karo
            // wo kuch kaam ke nahi hein, aage bhi kaam me nahi aane vale!!
            while(dq.size()>0  && dq.back() < nums[right]){
                dq.pop_back();
            }

            // Chote elements nikalne ke baad num[j] ko push karo
            dq.push_back(nums[right]);
            
            // Window size choti hein, usko badhao
            if(right - left +1 < k) right ++;

            // K ki window mil gai!!
            else if(right - left +1 == k){
                // 1) Calculate the answer!!
                // Push the front of dq, as it will be largest of the window(ensure while pushing
                // elements in deque, as we are popping smaller elements than pushing element). 
                ans.push_back(dq.front());

                // 2) Slide the window
                // If left index of current window index of larget element of current window
                // Then we need to pop it, as we are sliding the window
                // So, Remove the index present in front of deque.
                if(nums[left] == dq.front()) dq.pop_front();
                // slide window, by moving left and right pointer ahead by 1
                left++;
                right++;
            }
        }
        return ans;

        // Basically, we are storing elements in decreasing fashion inside queue,
        // so that element at front will always be maximum.

        // T.C-> O(2*N)
        // S.C-> O(K)
    }
-------------------------------------------------------------------------------------------------------------------------------------------------
5) Maximum Points You Can Obtain from Cards
https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/description/
a) Pahile k ele chi sum kaadh
b) Mg pahilyatna kadha, shevtun taka ani maximize karat chala ( notes bgh)

    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        // calculate sum of first k elements
        int sum = 0;
        for(int i=0;i<k;i++) sum += cardPoints[i];
        
        // As we need to maximize the sum, store it is ans variable to do
        // operations on sum 
        int ans = sum;

        // Point i -> k-1 and j -> n-1
        int i = k-1, j = n-1;

        // Go on removing from front and adding from back, until they move k steps
        while(i>=0 && j>=n-k){
            // remove from front
            sum -= cardPoints[i--];
            // add from back
            sum += cardPoints[j--];
            // Maximize the ans
            ans = max(ans, sum);
        }

        // return the maximum sum
        return ans;
    }

        // T.C-> O(2*k)
        // S.C-> (1)
-------------------------------------------------------------------------------------------------------------------------------------------------
6) Sum of minimum and maximum in every window of size k
Same as above approach, just add deque of mini and same logic copy pasted
See the code kalun jail. 
long long sumOfMaxAndMin(vector<int> &nums, int n, int k) {
	    // int n = nums.size();
        long long ans=0;
        // We wre using deque bcoz, here we want to deal with entire window of size k
        // i.e. to fetch maximum among k window size, for that we need to also pop
        // some elements from back as well, which are smaller than incoming.
        // And to store the maximums for next window.
        int left = 0, right = 0;
        deque<int> maxi, mini;
        while(right<n){
            // nums[right] se jitne smaller elements present hein queue mein, unko pop karo
            // wo kuch kaam ke nahi hein, aage bhi kaam me nahi aane vale!!
            while(maxi.size()>0  && maxi.back() < nums[right]){
                maxi.pop_back();
            }
            
            // same with mini 
            while(mini.size()>0  && mini.back() > nums[right]){
                mini.pop_back();
            }

            // elements nikalne ke baad num[j] ko push karo
            maxi.push_back(nums[right]);
            mini.push_back(nums[right]);
            
            
            // Window size choti hein, usko badhao
            if(right - left +1 < k) right ++;

            // K ki window mil gai!!
            else if(right - left +1 == k){
                // 1) Calculate the answer!!
                // Push the front of maxi, as it will be largest of the window(ensure while pushing
                // elements in deque, as we are popping smaller elements than pushing element). 
                int num = maxi.front() + mini.front();
                ans += num;

                // 2) Slide the window
                // If left index of current window index of larget element of current window
                // Then we need to pop it, as we are sliding the window
                // So, Remove the index present in front of deque.
                if(nums[left] == maxi.front()) maxi.pop_front();
                // same with mini
                if(nums[left] == mini.front()) mini.pop_front();

                // slide window, by moving left and right pointer ahead by 1
                left++;
                right++;
            }
        }
        return ans;
        // T.C-> O(2*N)
        // S.C-> O(2*K)
}
*****************************************************************************************************************************************************************
B) Variable size window

Note:
1) Size of window will be unknown, infact we have to remove that size as our answer in most of the cases!
2) In fixed size window: We were given size of window
   In variable size window: We have to find the size of window (maximum or minimum ). Basically maximize or minimize 
   the window size.
3) Yahe pe window tab hit hogi jab given condition window mein satisfy ho jaye!! Jaise ki if(sum == k), yaha apan 
   length nikal lenge window ki. matlab sum jo paryant k hot nahi to paryant window size wadhva, ani jar sum mothi 
   zali k pekshya, tar left madhaun elements kadhun kami kara WHILE LOOP laun.
4) Fixed size mein apun window size check kar rahe the, yaha apan condition check karenge.

A simple way to remember this is 
- At every step you will increase right by exactly one
- Also at every step you may increase left by 0 or 1 or more than 1 depending on whether your condition is not met 
  or overshot.

Identification->
1) Array|Subarray|K(sum)|K with some condition
2) String|Substring|K(sum)|K with some condition

General template:
    while(right<n){

        // Add element pointed by right into answer
        sum += A[right] OR Insert in map

        // Whenever sum exceeds k, remove elements from left ands stop when sum becomes
        // less than or equal to k
        while(sum>k){
            sum -= A[left];   OR Map operaions
            left++;
        }        

        // This will maximize length of window having sum equal to k
        // as we are not allowing sum to go beyond k.
    	// This if is mandotary!!
        if( sum == K){                         OR    (m.size() == k) // whenever any condition satisfies!!
            ans = max(ans, right-left+1);
        }

        // move right ahead always
        right++;
    }

Questions:

1) Subarray with given sum ( we have to return start and end index of that subarray)
https://practice.geeksforgeeks.org/problems/subarray-with-given-sum-1587115621/1?page=1&category[]=sliding-window&sortBy=difficulty
    vector<int> subarraySum(vector<int>arr, int n, long long s)
    {
        // if sum itself is zero, there cannot be any answer
        if(s==0) return {-1};
        int left =0, right= 0;
        long long sum = 0;
        while(right<n){
            // Add the element to sum
            sum += arr[right];
            
            // If some exceeds s, remove elements from left until sum is not less
            // or equal to s
            while(sum > s){
                sum -= arr[left];
                left++;
            }
            
            // if sum equal givem sum, return their indexes (1 based)
            if(sum == s){
                return {left+1, right+1};
            }
            
            // If sum is not still equal to s, move increase the window.
            right ++;
        }
        
        // If no such subarray, return -1
        return {-1};
    }
	// T.C-> O(2*N)
	// S.C-> O(1)
-------------------------------------------------------------------------------------------------------------------------------------------------
2) Longest Subarray with given Sum K(Positives)
https://www.codingninjas.com/studio/problems/longest-subarray-with-sum-k_6682399?utm_source=striver&utm_medium=website&utm_campaign=a_zcoursetuf

int longestSubarrayWithSumK(vector<int> A, long long k) {
    int n = A.size();
    int left = 0, right = 0;
    long long sum = 0;
    int ans = 0;
    while(right<n){
        // Add element pointed by right into answer
        sum += A[right];

        // Whenever sum exceeds k, remove elements from left ands stop when sum becomes
        // less than or equal to k
        while(sum>k){
            sum -= A[left];
            left++;
        }        

        // This will maximize length of window having sum equal to k
        // as we are not allowing sum to go beyond k.
        if(sum == k)
           ans = max(ans, right-left+1);

        // move right ahead always
        right++;
    }

    // return the max length
    return ans;
} 
	// T.C-> O(2*N)
	// S.C-> O(1)
	

Q. Will the discussed approach work with negative numbers in the array?
A. No. 
Because lets say in the given array [4,1,1,1,2,3,5] when we found the sum within the window to be greater than 
the desired value 5 (i=0, j=2 -> [4,1,1]), we started reducing the size of the window by doing i++. 
Here we assumed that once the sum of elements within the window becomes greater than 5 then increasing 
the window size will just add to the sum and hence we will not attain the sum 5 again. This is true when all 
the element are positive and hence reducing the window size by doing i++ makes sense. But this might not be 
true if array also contains negative numbers. Consider the array [4,1,1,-2,1,5], here we would have found the 
sum to be greater than 5 for i=0, j=2 and if we would have now started reducing the window size by doing i++, 
we would have missed the potential subarray (i=0, j=4).In short, the discussed approach will not work with array
having negative numbers.
-------------------------------------------------------------------------------------------------------------------------------------------------
3) Longest K unique characters substring ( k Pekshya jast unique characters nahi pahije, mhnje map chi size 
pekshya jast nahi jaun dyaychi)
https://practice.geeksforgeeks.org/problems/longest-k-unique-characters-substring0853/1

See the video from 28 minutes to get the idea if not
https://www.youtube.com/watch?v=Lav6St0W_pQ&list=PL_z_8CaSLPWeM8BDJmIYDaoQ5zuwyxnfj&index=10

    int longestKSubstr(string s, int k) {
        int n = s.size();
        unordered_map<char, int> m;
        
        int left = 0, right = 0;
        int ans = -1;
        
        while(right<n){
            // Increase the count of character in map, pointed by right pointer 
            m[s[right]]++;
            
            // Map madhe k pekshya jast characters aale mhnje given condition fail zali
            // mg left madhun kami karat yaa!!
            while(left<=right && m.size() >k){
                // remove character from left, by decreasing the count of char
                // pointed by left pinter
                m[s[left]]--;
                // Jar ekhadhya character cha count 0 zala mhnje kay ki window madhe
                // ek unique character kami zala mg map chi size pn kami vhayla pahije
                // mhanun jyachi frequency zero zali ahe, tyala map madhun kadhun taka
                // map madhun kadhlyavr map chi size kami hoel ani loop chya baher nighel
                // Mhnje ata apan ek character nighe paryant left pointer pudhe anla ani ata
                // pudchi window process kara!!
                if(m[s[left]] == 0){
                    m.erase(s[left]);
                }
                // move left ahead, to remove one unique character
                left++;
            }
            
            // Apan jevha ek unique character kadhun baher alo, tevha left pointer
            // tya kaadhlelya char chya just pudhe asel !!
            
            // Jar map chi size k ahe, mhnje kay ki current window madhe exactly
            // k unique characters ahet, mg window chi size consider kara!!	
            // THIS IF STATEMENT IS MANDOTARY
            if(m.size() == k){
                ans = max(ans, right-left+1);
            }
            
            // Move right pointer everytime!!
            right++;
        }
        
        // Return the max Length of window we got
        return ans;
    }

    Instead of erasing from map, we can also use a count variable technique as used in count anagrams pattern, 
    to reduce the space and time complexity.
    // TC - O(2N*logN) we are erasing from map
    // SC - O(26)

A bit optimized-> Not erasing from map, using count variable to store no. of unique characters
We were using maps size to know the no. of unique characters by erasing whenever the freq of any character 
goes zero. So here we will be using a count varible to store the no. of unique characters!!

Code-->
    int longestKSubstr(string s, int k) {
        int n = s.size();
        unordered_map<char, int> m;
        
        int left = 0, right = 0;
        int ans = -1;
        
        // Count will store no. of unique characters here
        int count = 0;
        
        while(right<n){
            // Increase the count of character in map, pointed by right pointer 
            m[s[right]]++;
            
            // When a new character comes in it's freq will be 1, it is unique so increase the count
            if(m[s[right]] == 1) count++;
            
            // unique characters(count) k pekshya jast zale mhnje givem condition fail zali
            // mg left madhun kami karat yaa!!
            while(left<=right && count >k){
                // remove character from left, by decreasing the count of char
                // pointed by left pointer
                m[s[left]]--;
                // Jar ekhadhya character chi freq 0 zala mhnje kay ki window madhe
                // ek unique character kami zala mg count kami zala pahije
                // mhanun jyachi frequency zero zali ahe,
                // count kami hoel ani loop chya baher nighel
                if(m[s[left]] == 0){
                    count--;
                }
                // move left ahead, to remove one unique character
                left++;
                // Mhnje ithe apan ek character nighe paryant left pointer pudhe anla ani ata
                // pudchi window process kara!!
            }
            
            // Apan jevha ek unique character kadhun baher alo, tevha left pointer
            // tya kaadhlelya char chya just pudhe asel !!
            
            // Jar count == K ahe mhnjech kay ki current window madhe exactly
            // k unique characters ahet, mg window chi size consider kara!!
            // THIS IF STATEMENT IS MANDOTARY
            if(count == k){
                ans = max(ans, right-left+1);
            }
            
            // Move right pointer everytime!!
            right++;
        }
        
        // Return the max Length of window we got
        return ans;
    }
	//T.C-> O(2*N)
	//S.C-> O(26)
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
4) Longest Substring Without Repeating Characters 
https://leetcode.com/problems/longest-substring-without-repeating-characters/description/
See last 5 minutes of video to get idea if not
https://www.youtube.com/watch?v=L6cffskouPQ&list=PL_z_8CaSLPWeM8BDJmIYDaoQ5zuwyxnfj&index=11

Approach1: This is the approach similar to above question, i.e. substring with k distinct characters

THINK OVER IT -->
	// IF SIZE OF WINDOW == NO. OF UNIQUE CHARACTERS, then we can say that this window
    // contains a substring which contains all unique characters!!
	SIZE OF WINDOW  = right - left + 1!
	NO. OF UNIQUE CHARACTERS = size of map!
	

    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        unordered_map<char,int> m;
        int l = 0, r = 0, ans = 0;

        // IF SIZE OF WINDOW == NO. OF UNIQUE CHARACTERS, then we can say that this window
        // contains a substring which contains all unique characters!!

        while(r<n){
            m[s[r]]++;

            // When window size goes greater than unique characters, it means the window contains
            // one or more duplicate characters, so we need to decrease the window size from left
            // And if for any character it's freq becomes zero, we delete it from map, to maintain the
            // condition that no. of unique chars == size of map!!
            while(left<=right && r-l+1 > m.size()){
                m[s[l]]--;
                if(m[s[l]] == 0) m.erase(s[l]);
                l++;
            } 

            // When the size of window becomes equal to no. of unique characters i.e. equal to size of
            // map, means we got one substring which has all uniqueu characters, so we maximize it's len
            if(r-l+1 == m.size()){
                ans = max(ans, r-l+1);
            }

            // We move right pointer always!!
            r++;
        }   

        // return maximum length of uniue characters substring!
        return ans;
    }
    // TC - O(2N*logN) we are erasing from map
    // SC - O(26)

Instead of erasing from map, we can also use a count variable technique as used in count anagrams pattern, to reduce the space and time complexity.
We were using maps size to know the no. of unique characters by erasing whenever the freq of any character goes zero
So here we will be using a count varible to store the no. of unique characters!!

Code-->
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        unordered_map<char,int> m;
        int l = 0, r = 0, ans = 0;

        // IF SIZE OF WINDOW == NO. OF UNIQUE CHARACTERS, then we can say that this window
        // contains a substring which contains all unique characters!!

        // Count will store no. of unique characters here
        int count = 0;

        while(r<n){
            m[s[r]]++;
            // When a new character comes in it's freq will be 1, it is unique so increase the count
            if(m[s[r]] == 1) count++;

            // When window size goes greater than unique characters, it means the window contains
            // one or more duplicate characters, so we need to decrease the window size from left
            // And if for any character it's freq becomes zero, we reduce the count one unique character 
            // has gone!!
            while(left<=right && r-l+1 > count){
                m[s[l]]--;
                // All occurences of a characters are removed, so one unique character is gone, so reduce
                // count.
                if(m[s[l]] == 0)count--;
                l++;
            } 

            // When the size of window becomes equal to no. of unique characters i.e. count
            // means we got one substring which has all unique characters, so we maximize it's len
            if(r-l+1 == count){
                ans = max(ans, r-l+1);  
            }

            // We move right pointer always!!
            r++;
        }   

        // return maximum length of uniue characters substring!
        return ans; 
    }
	//T.C-> O(2*N)
	//S.C-> O(26)
--------OR-----------------
Approach2:
Eka pan character cha occurence 1 pekshya jast nahi pahije, mhnje map madhlya eka pn character cha 
count 1 pekshya motha nahi zala pahuje

    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int right=0,left = 0;
        int ans = 0;

        // map to store the frequency!!
        unordered_map<char, int> m;
        while(right<n){
            // Add frequency of current character
            m[s[right]] ++;
            // If freq goes more than 1, go on decreasing the frequencies from left till
            // the freq of right is no more greater than 1
            while(m[s[right]]>1){
                m[s[left]]--;
                left++;
            }

            // Jevha right chi frequency 1 kivva 1 pekshya choti hoel, tevha left pointer thambel
            // ani to kuthe point karat asel jithe left pointer right wala character pass karun ala ae
            // tyamulech tr tyachi(right char) chi frequency less or equal 1 zali na, mg atta left
            // ani right madhe sagle uniquq characters ahet tr ata length maximize kara!!
            // dry run on-> "abcade" ithe pahilyanda jevha aatla while loop execute hoel tevha
            //  left 1st index la asel ani rught 3rd la (0-based madhe) mhnjech konte characters?-> 
            // "bca" mhnje ki left pointer a la sodun ala!!
            ans = max(ans, right-left+1);

            right++;
        }
        // return the maximum length
        return ans;
    }
	// T.C-> O(2*N)
	// S.C-> O(26)
-----------------------------------------------------------------------------------------------------------------------------------------
5) Fruits Into Baskets ( We can pick maximum 2 types of fruits, same question as longest substring having k 
distinct characters, here k == 2) ( 2 ch types che pahije asa kahi nahi, jastit jast 2 type che gheu shakto asa, 
1 pn chalel)
https://leetcode.com/problems/fruit-into-baskets/

We have to pick fruits in order as they are i.e. substring, this gives us a hint of sliding window
with one more condition that we can pick only two types of fruits.
i.e. frequency must not exceed 2!!! And when we need to pick the third type of fruit y picking two types before, 
we need to stop here as we are not allowed to pick more that 2 types of fruis!!

The question is-> Maximum of length of subarray(maximum toys) which has at most 2 distinct/unique elements!!

See last 5 minutes of video rather
https://www.youtube.com/watch?v=seOKHXB_w74&list=PL_z_8CaSLPWeM8BDJmIYDaoQ5zuwyxnfj&index=12&ab_channel=AdityaVerma

    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();

        unordered_map<int,int> m;
        int l = 0, r=0, ans = 1;

        // to store no. of unique characters!!
        int count = 0;  // Instead of this we can use map size, but we have to erase charcter from it
                        // whenever freq of any character goes to 0 

        while(r<n){
            // Increase the count of character in map, pointed by right pointer
            m[fruits[r]]++;
            // When a new character comes in it's freq will be 1, it is unique so increase the count
            if(m[fruits[r]] == 1) count++;

            // unique characters(count) 2 pekshya jast zale mhnje givem condition fail zali
            // mg left madhun kami karat yaa!!
            while(l<=r && count>2){
                // remove character from left, by decreasing the count of char
                // pointed by left pinter
                m[fruits[l]]--;
                // Jar ekhadhya character chi freq 0 zala mhnje kay ki window madhe
                // ek unique character kami zala mg count kami zala pahije
                // mhanun jyachi frequency zero zali ahe,
                // count kami hoel ani loop chya baher nighel
                if(m[fruits[l]] == 0) count--;
                // move left ahead, to remove one unique character
                l++;
            } 
            
            // Jar count <= 2 ahe mhnjech kay ki current window madhe 2 kivva 2 pekshya kami
            // types che fruits ale ahet( 2 ch types che pahije asa kahi nahi, jastit jast 2 type che gheu shakto asa!) mg window chi size consider kara!!
            if(count <= 2){
                ans = max(ans, r-l+1);
            }
            
            // Move right pointer everytime!!
            r++;
        }

        return ans;
        //T.C-> O(2*N)
	//S.C-> O(N)
    }
--------------------------------------------------------------------------------------------------------------------------------------------------------
6) Max Consecutive Ones III
https://leetcode.com/problems/max-consecutive-ones-iii/description/
https://www.youtube.com/watch?v=Gl-8HLvV8bc&ab_chann    el=AyushiSharma


    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();
        int l = 0, r = 0;
        int ans = 0;
	
	    // To count no. of zeroes till now, in a window!
        int count = 0;

        while(r<n){
            // If we encounter 0, increase the count
            if(nums[r] == 0) count++;

            // If count of 0 in a window goes beyond k, reduce the window from left until we
            // get count of zero's again less  or equal to k
            while(l<=r && count>k){
                if(nums[l] == 0) count--;
                l++;
            } 
            
            // If count of zeroes lies under k, consider this window!!
            if(count<=k){
                ans = max(ans, r-l+1);
            }

            // Increase the right pointer always!! 
            r++;
        }

        // Return the max length we get! 
        return ans;

        // T.C-> O(2*N)
        // S.C-> (1)
    }
------------------------------------------------------------------------------------------------------------------------------------------------------------------
7)  Longest Repeating Character Replacement
https://leetcode.com/problems/longest-repeating-character-replacement/description/
See notes on A2Z for idea

    int characterReplacement(string s, int k) {
        int n = s.size();
        int l = 0, r = 0, ans = 0;

        // Store maximum frequency in a window
        int maxi = 0;

        unordered_map<char, int> m;

        while(r<n){
            // Push the character into map
            m[s[r]]++;

            // Update the maximum frequency
            maxi = max(maxi, m[s[r]]);

            // If no. of charcters we can replace (window_size - max frequency) exceeds k
            // We will go on removing characters from left. And stop when this no. becomes
            // less or equal k, we are reducing the window size from left here.
            while( (r-l+1 - maxi)  > k){
                m[s[l]]--;
                l++;
            }

            // If no. of charcters we can replace (window_size - max frequency) is less
            // or equal to k, then we can replace them so consider this window.
            if((r-l+1 - maxi) <= k){
                ans = max(ans, r-l+1);
            }
            
            // Move the window ahead always, it is going to shrink from left; dw
            r++;
        }

        // return the maximum length we got
        return ans; 
    }
        // T.C-> O(2*N)
        // S.C-> (26)
------------------------------------------------------------------------------------------------------------------------------------------------------------------
8) Longest Substring with At Most K Distinct Characters
https://www.codingninjas.com/studio/problems/longest-substring-with-at-most-k-distinct-characters_2221410?utm_source=striver&utm_medium=website&utm_campaign=a_zcoursetuf

*Same code as exactly K distinct characters, just replaced count == k with count <= k; while maximizing the answer.

int kDistinctChars(int k, string &s)
{
    int n = s.size();
    unordered_map<char, int> m;
    
    int left = 0, right = 0;
    int ans = -1;
    
    // Count will store no. of unique characters here
    int count = 0;
    
    while(right<n){
        // Increase the count of character in map, pointed by right pointer 
        m[s[right]]++;
        
            // When a new character comes in it's freq will be 1, it is unique so increase the count
        if(m[s[right]] == 1) count++;
        
        // unique characters(count) k pekshya jast zale mhnje givem condition fail zali
        // mg left madhun kami karat yaa!!
        while(left<=right && count >k){
            // remove character from left, by decreasing the count of char
            // pointed by left pointer
            m[s[left]]--;
            // Jar ekhadhya character chi freq 0 zala mhnje kay ki window madhe
            // ek unique character kami zala mg count kami zala pahije
            // mhanun jyachi frequency zero zali ahe,
            // count kami hoel ani loop chya baher nighel
            if(m[s[left]] == 0){
                count--;
            }
            // move left ahead, to remove one unique character
            left++;
            // Mhnje ithe apan ek character nighe paryant left pointer pudhe anla ani ata
            // pudchi window process kara!!
        }
        
        // Apan jevha ek unique character kadhun baher alo, tevha left pointer
        // tya kaadhlelya char chya just pudhe asel !!
        
        // Jar count <= K ahe mhnjech kay ki current window madhe at most
        // k unique characters ahet, mg window chi size consider kara!!
        // THIS IF STATEMENT IS MANDOTARY
        if(count <= k){
            ans = max(ans, right-left+1);
        }
        
        // Move right pointer everytime!!
        right++;
    }
    
    // Return the max Length of window we got
    return ans;
}

        // T.C-> O(2*N)
        // S.C-> (26)
------------------------------------------------------------------------------------------------------------------------------------------------------------------
9) Minimum Window Substring
https://leetcode.com/problems/minimum-window-substring/description/
**Once we hit the condition, keep shrinking from left until the condition is still satisfying!!

    string minWindow(string s, string t) {
        int n = s.size();
        int l = 0, r = 0, start = -1, end = -1, len = INT_MAX;

        unordered_map<char,int> m;
        for(auto &ch:t){
            m[ch]++;
        }

        int count = m.size();
        int k = count;

        while(r<n){
            // If traversing character is present in map, that means it is the part of "t"
            if(m.find(s[r]) != m.end()){
                // reduce the frequency of that character in map
                m[s[r]]--;
                // if frequency of currentr character becomes 0, that means all occurrences
                // of that character matches, so reduce the count of distinct characters
                if(m[s[r]] == 0) count--;
            }

            // COUNT BECOMES 0, MEAN WE MATCHED ALL CHARACTERS OF "T" WITH SOME PART OF "S"

            // keep shrinking the window till you keep getting count as 0, as we want shortest length 
            // This will work as we are allowing frequncy to go negative, indicating there are extra
            // matches present, so try to reduce them and see if we can get count still 0.
            while(l<=r && count == 0){
                // Update the length, start and end point of window if minimum length is found.
                if(r-l+1<len){
                    len = r-l+1;
                    start = l;
                    end = r;
                }
                // If left character is found in window, increase it's frequency to restore the
                // characters in t, to process the further windows. And as count is storing the no. of
                // unique characters present i string "t", so increase count as we get a new occurung
                // character, mhnje window madhe tyache sagle occurences gele hote, ata window pudhe
                // saraktana tyacha ek character gela window madhun mg tyala parat restore kara t chya
                // corresponding as a unique character, mhnje count vadhva( se anagram code!)
                // Basically we are making "t" valid again, to process further windows
                if(m.find(s[l]) != m.end()){
                    m[s[l]]++;
                    if(m[s[l]] == 1)count ++;
                }
                // decrease the window size, by increasing the left pointer
                l++;
            }

            // Move window ahead everytime, jar kahi gadbad zali tr varcha while loop te baghun gheil
            r++;
        }

        // No match found!!
        if(start == -1 || end == -1) return ""; 

        // String store karun return kara
        string ans = "";
        for(int i = start;i<=end;i++){
            ans += s[i];
        }
        return ans;
    }


        // T.C-> O(2*N)
        // S.C-> (26)

*******************************************************************************************************************************************************************
C) atMost Vala pattern, count number of subarrays (variable size only, but of counting subarrays!)
Keep in mind:
1) Exactly(k) = atMost(k) - atMost(k-1)
2) ABove logic is used if we are asked for COUNT/NUMBER OF... 
2) In atmost funcntion: "ANS += RIGHT - LEFT + 1"

Questions:
1) Binary Subarrays With Sum
https://leetcode.com/problems/binary-subarrays-with-sum/description/
Explanation:
https://www.youtube.com/watch?v=Pkqq6kv2E6k&ab_channel=CodingSamurai%27s


    int atMost(vector<int>& nums, int k){
        int n = nums.size();
        // To store total number of subarrays
        int count = 0;
        int sum = 0, l = 0, r = 0;
        while(r<n){
            // Add ele pointed by right pointer
            sum += nums[r];

            // If sum exceeds, reduce it from left until it falls back to <= k
            while(l<=r && sum > k){
                sum -= nums[l];
                l++;
            }

            // If a window gives us a sum atmost k (<=) add it's size to the answer.
            // Because every possible subarray in this window will give sum <= k
            // And all possible subarray are formed by addition of all sizes of windows!!
            // Read notes
            if(sum <= k){
                count += r-l+1;
            }

            // Move the window ahead always, it is going to shrink from left; dw
            r++;
        }

        // return the total number of subarrays with sum 0, 1, 2, ...k
        return count;
    }

    int numSubarraysWithSum(vector<int>& nums, int goal) {
        // exactly(k) = atMost(k) - atMost(k-1)
        return atMost(nums, goal) - atMost(nums, goal-1);
    }
        // T.C-> O(2*N)
        // S.C-> (1)
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
2) Count Number of Nice Subarrays
https://leetcode.com/problems/count-number-of-nice-subarrays/description/
Similar to above approach!!!!
In above problem, we were keeping the track of sum; and here we just keep the track
of odd numbers in the window.

    int atMost(vector<int>& nums, int k){
        int n = nums.size();

        // count number of subarrays with at most k odds
        int ans = 0, l = 0, r = 0;

        // no. of odds in each subarray
        int odds = 0;

        while(r<n){
            // If the ele is odd, then increase the odd count
            if(nums[r]%2 == 1) odds++;

            // If odd count exceeds k, reduce the window from left
            // and do odd count-- if and only if when it is left ele is odd
            while(l<=r && odds>k){
                if(nums[l]%2 == 1) odds--;
                l++;
            }
            
            // If odds in current are atmost k(<=k) add the size of this window into count
            // Because every possible subarray in this window will give count <= k
            // And all possible subarray are formed by addition of all sizes of windows!!
            if(odds <= k){
                ans += r-l+1;
            }

            // Move the window ahead always, it is going to shrink from left; dw
            r++;
        } 

        // return the total number of subarrays with odd count of 0, 1, 2, ...k
        return ans;
    }

    int numberOfSubarrays(vector<int>& nums, int k) {
        // Exactly(k) = atMost(k) - atMost(k-1) 
        return atMost(nums,k) - atMost(nums,k-1);
    }

        // T.C-> O(2*N)
        // S.C-> (1)
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
3) Number of Substrings Containing All Three Characters
https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/description/

Exactly(k) = atMost(k) - atMost(k-1) 
return atMost(s,3) - atMost(s,2); i.e.

"No. of substring with at most 3 unique characters"
		   minus
"No. of substring with at most 2 unique characters "

Ans this atMost function is similar to above 2 problems.
And logic to maintain unique characters is used of K unique/distinct characters question.

    int atMost(string &s, int k){
        int n = s.size();

        // WE CAN HAVE AT MOST K UNIQUE CHARACTERS IN A SUBSTRING

        // count number of subarrays with at most k characters
        int ans = 0, l = 0, r = 0;

        // IF USING MAP IS GIVING TLE, WE CAN ALSO USE VECTOR OF SIZE 26, AND STORE CHARACTERS AS [ch - 'a']

        unordered_map<char,int> m;

        // To store unique characters of a window
        int count = 0;

        while(r<n){
            // Increase the count of character in map, pointed by right pointer
            m[s[r]]++;
            // When a new character comes in it's freq will be 1, it is unique so increase the
            // count            
            if(m[s[r]] == 1) count++;

            // unique characters(count) k pekshya jast zale mhnje givem condition fail zali
            // mg left madhun kami karat yaa!!
            while(l<=r && count>k){
                // remove character from left, by decreasing the count of char
                // pointed by left pointer
                m[s[l]]--;
                // Jar ekhadhya character chi freq 0 zala mhnje kay ki window madhe
                // ek unique character kami zala mg count kami zala pahije
                // mhanun jyachi frequency zero zali ahe,
                // count kami hoel ani loop chya baher nighel
                if(m[s[l]] == 0) count--;
                // move left ahead, to remove one unique character
                l++;
                // Mhnje ithe apan ek character nighe paryant left pointer pudhe anla ani ata
                // pudchi window process kara!!
            }
            
            // Jar count <= K ahe mhnjech kay ki current window madhe atMost
            // k unique characters ahet, mg window chi size add kara!!
            // Because every possible subarray in this window will give count <= k
            // And all possible subarray are formed by addition of all sizes of windows!!
            if(count <= k){
                ans += r-l+1;
            }

            // Move the window ahead always, it is going to shrink from left; dw
            r++;
        } 

        // return the total number of subarrays with 0, 1, 2, ...k unique characters
        return ans;
    }

    int numberOfSubstrings(string s) {
        // Exactly(k) = atMost(k) - atMost(k-1) 
        return atMost(s,3) - atMost(s,2);
    }

        // T.C-> O(2*N)
        // S.C-> (3)
----------------
Approach2: Samjayla avghad ahe jara, pn samajto ani chota ahe

    int numberOfSubstrings(string s) {
        // Exactly(3) = atMost(3) - atMost(2) 
        // return atMost(s,3) - atMost(s,2);
        int n = s.size();
        int ans = 0;
        int i = 0, j = 0;
        int count[3] = {0};
        while(j < n){
            count[s[j]-'a']++;
            // When all count becomes 1, then this loop will execute!
            while(i<=j && count[0]>0 && count[1]>0 && count[2]>0){
                count[s[i]-'a']--;
                i++;
            }

            // We are adding window size only here!! Attaparyant i size chya window madhe te 3 characters
            // ahet! ASA!!!
            ans += i;
            j++;
        }
        return ans;
    }

    // TC - O(2*N)
    // SC - O(1)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------
4) Subarrays with K Different Integers
https://leetcode.com/problems/subarrays-with-k-different-integers/description/
Same to same code as above!!
The code is exactly same!!

        // Exactly(k) = atMost(k) - atMost(k-1)

    int atMost(vector<int> &nums, int k){
        int n = nums.size();

        // WE CAN HAVE AT MOST K UNIQUE ELEMENTS IN A ARRAY

        // count number of subarrays with at most k elements
        int ans = 0, l = 0, r = 0;

        unordered_map<int,int> m;

        // To store unique elements of a window
        int count = 0;

        while(r<n){
            // Increase the count of element in map, pointed by right pointer
            m[nums[r]]++;
            // When a new element comes in it's freq will be 1, it is unique so increase the
            // count            
            if(m[nums[r]] == 1) count++;

            // unique elements(count) k pekshya jast zale mhnje givem condition fail zali
            // mg left madhun kami karat yaa!!
            while(l<=r && count>k){
                // remove element from left, by decreasing the count of element
                // pointed by left pointer
                m[nums[l]]--;
                // Jar ekhadhya element chi freq 0 zala mhnje kay ki window madhe
                // ek unique element kami zala mg count kami zala pahije
                // mhanun jyachi frequency zero zali ahe,
                // count kami hoel ani loop chya baher nighel
                if(m[nums[l]] == 0) count--;
                // move left ahead, to remove one unique element
                l++;
                // Mhnje ithe apan ek element nighe paryant left pointer pudhe anla ani ata
                // pudchi window process kara!!
            }
            
            // Jar count <= K ahe mhnjech kay ki current window madhe atMost
            // k unique elements ahet, mg window chi size add kara!!
            // Because every possible subarray in this window will give count <= k
            // And all possible subarray are formed by addition of all sizes of windows!!
            if(count <= k){
                ans += r-l+1;
            }

            // Move the window ahead always, it is going to shrink from left; dw
            r++;
        } 

        // return the total number of subarrays with 0, 1, 2, ...k unique elements
        return ans;
    }

    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return atMost(nums, k) - atMost(nums, k-1);
    }

        // T.C-> O(2*N)
        // S.C-> (N)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------





DIFFERENT PATTERN
https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/submissions/987953407/
Number of Substrings Containing All Three Characters
   int numberOfSubstrings(string s) {
        int n = s.size();
        int ans = 0;
        int i = 0, j = 0;
        int count[3] = {0};
        while(j < n){
            count[s[j]-'a']++;
            while(i<=j && count[0]>0 && count[1]>0 && count[2]>0){
                count[s[i]-'a']--;
                i++;
            }
            ans += i;
            j++;
        }
        return ans;
    }
    // TC - O(2*N)
    // SC - O(1)
********************************************************************************************************************************************************************

ITHUN KHAALCHE PAHAYCHE AHE TULA!!
https://www.codingninjas.com/studio/problems/minimum-window-subsequence_2181133?leftPanelTab=1
Minimum Window Subsequence

string minWindow(string s, string t)
{
	int n = s.size(), k = t.size();
	int i = 0, j = 0;
	unordered_map<char,int>mp;
	for(auto it : t){
		mp[it]++;
	}
	int count = k;
	int ans = 1e9, left = -1, right = -1;
	for(int i=0; i<n; i++){
		if(s[i] == t[j]){
			j++;
		}
		if( j == k){
			int end  = i;
			j--;
			while(j>=0){
				if(s[i] == t[j]){
					j--;
				}
				i--;
			}
			i++;
			j++;
			if(end - i < ans){
				ans = end - i;
				left = i;
				right = end;
			}
		}
	}
	if(ans == 1e9){
		return "";
	}
	string res = "";
	for(int i=left; i<=right; i++){
		res+=s[i];
	}
	return res;
	// TC - O(N*N)
}
https://leetcode.com/problems/minimum-size-subarray-sum/description/
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int i = 0, j = 0;
        int sum = 0, ans = 1e9;
        while(j < n){
            sum+=nums[j];
            while(i<=j && sum>=target){
                ans = min(ans,j-i+1);
                sum-=nums[i];
                i++;
            }
            j++;
        }
        if(ans == 1e9){
            return 0;
        }
        return ans;
    }
    // TC - O(N)
    // SC - O(1)

https://leetcode.com/problems/replace-the-substring-for-balanced-string/description/
Replace the Substring for Balanced String
   int balancedString(string s) {
        int n = s.size(), k=n/4;
        int i = 0, j = 0;
        unordered_map<char,int>mp;
        for(auto it : s){
            mp[it]++;
        }
        int ans = 1e9;
        while(j < n){
            mp[s[j]]--;
            while(i<n && mp['Q']<=k && mp['W']<=k && mp['E']<=k && mp['R']<=k){
                mp[s[i]]++;
                ans = min(ans, j-i+1);
                i++;
            }
            j++;
        }
        return ans;
    }

https://leetcode.com/problems/permutation-in-string/description/
Permutation in String(anagram)
   bool checkInclusion(string s1, string s2) {
        int k = s1.size(), n=s2.size();
        unordered_map<char,int>mp;
        for(auto it : s1){
            mp[it]++;
        }
        int i = 0, j = 0, count = mp.size();
        while(j < n){
            if(mp.find(s2[j])!=mp.end()){
                mp[s2[j]]--;
                if(mp[s2[j]]==0){
                count--;
                }
            }
            if(j-i+1<k){
                j++;
            }
            else{
                if(count == 0){
                    return true;
                }
               if(mp.find(s2[i])!=mp.end()){
                   mp[s2[i]]++;
                   if(mp[s2[i]]==1){
                   count++;
                   }
               }
               i++,j++;
            }
        }
        return false;
    }


https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/description/
(remaining)


