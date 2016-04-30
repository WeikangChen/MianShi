#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define PAIR string
// base class Quote : value coudld be buy_value or sell_value depend on its derived type

struct Quote
{
    string bank;
    int time;
    double value;
    Quote(string _bk, int _ts=0, double _val=0): bank(_bk), time(_ts), value(_val) {}
};

// derived class for buy
struct BuyQuote: public Quote
{
    BuyQuote(string _bk, int _ts=0, double _val=0):Quote(_bk, _ts, _val) {}
    static bool best_compare(BuyQuote q1, BuyQuote q2) {return q1.value > q2.value;}
};

// derived class for sell
struct SellQuote: public Quote
{
    SellQuote(string _bk, int _ts=0, double _val=0):Quote(_bk, _ts, _val) {}
    static bool best_compare(SellQuote q1, SellQuote q2) {return q1.value < q2.value;}
};

// Heap + Hash: compund data structure, we use them for
// Heap: to sort best quote, could be get through top()
// Hash: to retrieve the corresponding heap position and vaule
// We use template for two kind of quote: buy and sell
template <class T>
class HashHeap
{
  private:
    unordered_map<string, int> hsBank;
    vector<T> m_array;

  public:
    HashHeap() {}
    T top() {return m_array[0];}
    void clear() {
        hsBank.clear();
        m_array.clear(); 
    }
    
    void insert(T quote)
    {
        if(hsBank.find(quote.bank) != hsBank.end())
        {
            int pos = hsBank[quote.bank];
            T pre_quote = m_array[pos];
            if(pre_quote.time > quote.time) return;

            m_array[pos] = quote;
            if(T::best_compare(quote, pre_quote)) // heapify time comple is O(lg(sizeof_bank))
            {
                heapify_up(pos);
            }
            else
            {
                heapify_down(pos);
            }
        }
        else
        {
            push(quote);
        }
        
    }
    
    void push(T quote) {
        m_array.push_back(quote);
        int pos = m_array.size()-1;
        hsBank[quote.bank] = pos;
        heapify_up(pos);
    }
    
    void heapify_up(int i) {
        if(i == 0) return;
        int p = (i-1) / 2;
        if(T::best_compare(m_array[i], m_array[p])) {
            swap(m_array[i], m_array[p]);
            hsBank[m_array[i].bank] = i;
            hsBank[m_array[p].bank] = p;
            heapify_up(p);
        }
    }
    
    void heapify_down(int i)
    {
        const int n = m_array.size();
        int l = 2*i + 1;
        int r = 2*i + 2;
        int p = i;
        if(l < n && !T::best_compare(m_array[p], m_array[l])) p = l;  
        if(r < n && !T::best_compare(m_array[p], m_array[r])) p = r;
        if(p != i) {
            swap(m_array[i], m_array[p]);
            hsBank[m_array[i].bank] = i;
            hsBank[m_array[p].bank] = p;
            heapify_down(p);
        }
    }
    
    
    void check_timestamp(int cur_time) {
        
        bool require_heapify = false;
        if(m_array.empty()) return;
        int i = 0;
        while(i < m_array.size()) {
            if(cur_time > m_array[i].time + 3) 
            {
                require_heapify = true;
                erase(i);
            }
            else {
                i++;
            }
        }
        
        if(!require_heapify) return;
        
        for(int i = m_array.size()/2; i >= 0; --i) {
            heapify_down(i);
        }
    }
    
    void erase(int i) {
        int n = m_array.size();
        if(i >= n) return;
        if(i != n-1) {
            swap(m_array[i], m_array[n-1]);
            hsBank[m_array[i].bank] = i;
        }
        m_array.pop_back();
    } 

};


class Solution {
private:
    unordered_map<PAIR, HashHeap<BuyQuote> > mapPairBuy;
    unordered_map<PAIR, HashHeap<SellQuote> > mapPairSell;
    unordered_set<PAIR> setPairs;

public:
    unordered_set<PAIR> &GetAllCurrencyPairs(){
        return setPairs;
    }
    
    void check_timestamp(int time) {
        unordered_map<PAIR, HashHeap<BuyQuote> >::iterator it = mapPairBuy.begin();
        for(; it != mapPairBuy.end(); ++it) {
            it->second.check_timestamp(time);
        }
    }

    void process(vector<string> quote)
    {
        int time_stamp = stoi(quote[0]);
        string pair = quote[1];
        string bank = quote[2];
        double buy_value = stod(quote[3]);
        double sell_value = stod(quote[4]);
        
        check_timestamp(time_stamp);
        
        if(setPairs.find(pair) == setPairs.end())
            setPairs.insert(pair);
        
        if(mapPairBuy.find(pair) == mapPairBuy.end())
            mapPairBuy[pair] =  HashHeap<BuyQuote>();
        if(mapPairSell.find(pair) == mapPairSell.end())
            mapPairSell[pair] = HashHeap<SellQuote>();
            
            
        HashHeap<BuyQuote> &buyHeap = mapPairBuy[pair];
        HashHeap<SellQuote> &sellHeap = mapPairSell[pair];
        
        buyHeap.insert(BuyQuote(bank, time_stamp, buy_value));
        sellHeap.insert(SellQuote(bank, time_stamp, sell_value));
    }
    
    void Query(string pair)
    {
        if(mapPairBuy.find(pair) == mapPairBuy.end() || mapPairSell.find(pair) == mapPairSell.end())
        {
            cout << "Failed to find " << pair << endl;
            return;
        }
        HashHeap<BuyQuote> buyHeap = mapPairBuy[pair];
        HashHeap<SellQuote> sellHeap = mapPairSell[pair] ;
        
        BuyQuote bestBuyQuote = buyHeap.top();
        SellQuote bestSellQuote = sellHeap.top();
        
        cout << bestBuyQuote.time << ": Best " << pair << " Buy = "<< bestBuyQuote.value << " from " << bestBuyQuote.bank << endl;
        cout << bestSellQuote.time << ": Best " << pair << " Sell = "<< bestSellQuote.value << " from " << bestSellQuote.bank << endl;  
    }
};
int main () {
    // Initialization 
    //
    // In this part of the program you can perform any kind of
    // initialization routine before processing the stream 
    // of data.
    Solution sol;
    
    std::string line;
    std::vector<std::string> quote; 
    std::string item; 
    while(std::getline(std::cin, line)) {
        if(! line.empty()) {
            quote.clear(); 
            std::istringstream ss(line); 
            while (std::getline(ss, item, '|')) {
                quote.push_back(item);
            } 
            // Step 1: Process quote. 
            sol.process(quote);
            
            // Step 2: Query 
            unordered_set<PAIR> allpairs = sol.GetAllCurrencyPairs();
            unordered_set<PAIR>::iterator it = allpairs.begin();
            for( ; it != allpairs.end(); ++it )
                sol.Query(*it);
        }
    }
    return 0;
}
