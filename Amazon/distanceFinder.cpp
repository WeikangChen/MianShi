/* This class will be given a list of words (such as might be tokenized
 * from a paragraph of text), and will provide a method that takes two
 * words and returns the shortest distance (in words) between those two
 * words in the provided text. 
 * Example:
 *   WordDistanceFinder finder = new WordDistanceFinder(Arrays.asList("the", "quick", "brown", "fox", "quick"));
 *   assert(finder.distance("fox","the") == 3);
 *   assert(finder.distance("quick", "fox") == 1);
 
 */

class WordDistanceFinder {
private:
    unordered_map<string, vector<int> > mapIndex;
    WordDistanceFinder(vector<string> strs)
    {
        mapIndex.clear();
        for(int i = 0; i < strs.size(); ++i)
        {
            mapIndex[strs[i]].push_back(i);
        }
    }
    
    int ditance(string word1, string word2) {
    {
        if(mapIndex.find(word1) == maxIndex.end() || mapIndex.find(word1) == maxIndex.end() ) return -1;
        vector<int> indx1 = mapIndex[word1];
        vector<int> indx2 = mapIndex[word2];
        int min_distacne = INT_MAX;
        
        int i = 0, j =0;
        while(i < indx1.size() && j < indx2.size()) {
            int idx1 = indx1[i];
            int idx2 = indx2[j];
            min_distace = min(min_distace, abs(idx1 - idx2));
            
            if(idx1 < idx2) {
                i++;
            } else {
                J++;
            }
        }
        
        return min_distance;
    }
}



hs["the"] = {0};
hs["quick"] = {1, 4};
hs["brown"] = {2};
hs["fox"] = {3};
