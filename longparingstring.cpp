#include<iostream>
#include<string>
using namespace std;

class solution {
    public:
        string longestPalidrome(const string& s) {
            if (s.empty()) return s;

            int len = s.size();
            int idx = 0;
            int max_len = 0;
            int start = 0;

            while (idx < len) {
                int right = idx;
                int left = idx;
                //字符相等，向后偏移 
                while (idx < len && s[idx] == s[idx+1]) {
                    right++;
                    idx++;
                }
                // 
                while (right < len && left >= 0 && s[right] == s[left]) {
                    right++;
                    left--;
                }
                right--;
                left++;
                if (max_len < right - left + 1) {
                    max_len = right - left + 1;
                    start = left;
                }
                idx++;
            }

            return s.substr(start, max_len);
        }
};

int main(int argc, char *argvp[]) {
    string str = "abc";
    solution obj;
    string substr = obj.longestPalidrome(str);
    cout << "substr:"<<substr << endl;
    return 0; 
}
