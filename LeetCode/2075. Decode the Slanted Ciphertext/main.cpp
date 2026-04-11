class Solution {
public:
    string decodeCiphertext(string encodedText, int rows) {
        int n = encodedText.size();
        int colSize = n/rows;
        string decoded;
        decoded.reserve(n);

        for(int diag=0; diag<colSize; ++diag) {
            for(int row=0; row<rows; ++row) {
                int idx = row*colSize + row + diag;
                if(idx < (row+1)*colSize) {
                    decoded.push_back(encodedText[idx]);
                }
                else {
                    break;
                }
            }
        }

        // Remove the trailing spaces
        int decodedSize;
        for(decodedSize=decoded.size()-1; decodedSize>=0; --decodedSize) {
            if(decoded[decodedSize] != ' ') {
                break;
            }
        }
        decoded.resize(decodedSize+1);
        return decoded;
    }
};
