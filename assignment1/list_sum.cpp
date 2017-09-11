#include <iostream>

using namespace std;

const bool DEBUG = true;

void repeat_print(int count, char letter){
    if (count == 0){
        return;
    }
    if (count < 0){
        count = -count;
        letter = '+';
    }
    for (int i = 0; i < count; i++)
        cout << letter;
}


//this function prints the arrays. 
void printarray (int nums[], int len) {

    int j;     
    for (j = 0; j < len; j++) {
        int spaces = 3;
        if (nums[j] < 0)
            spaces--;
        if (nums[j] >= 10 || nums[j] <= -10)
            spaces--;
        cout << nums[j];
        repeat_print(spaces, ' ');
    }
    cout << endl;
    return; 
}

int main(){
    int nums[] = {-1, 2, 4, -10, 3, 3, -6, 2, 1, 3, -2, 1};
    int len = 12;
    
    int this_sum = 0;
    int max_sum = 0;
    int this_length = 0;
    int min_length = len;
    int start = 0;
    int end = 0;
    int best_start, best_end;

    for (int i = 0; i < len; i++){
       
    
        
        this_sum += nums[i];
        this_length += 1;
        end = i;

        if (this_sum > max_sum && this_length < min_length){
            max_sum = this_sum;
            best_end = end;
            best_start = start;
        }

        if (this_sum <= 0){
            this_sum = 0;
            start = i+1;
            this_length = 0;
        }
        
        if (DEBUG){
            printarray(nums, len);

            repeat_print(i*4, ' ');
            cout << "__" << endl;

            repeat_print(start*4, ' ');
            repeat_print((this_length)*4-3, '_');
            cout << " " << this_sum;
            cout << endl;

            cout << "max sum: " << max_sum << " from " << best_start << " to " << best_end << endl << endl;
        }
    }
    cout << "max sum: " << max_sum << " from " << best_start << " to " << best_end << endl << endl;
        
}


