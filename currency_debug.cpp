#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
using namespace std;

#define PAIR string

struct Quote
{
    string bank;
    int time;
    double value;
    Quote(string _bk, int _ts=0, double _val=0): bank(_bk), time(_ts), value(_val) {}
    void print() {
        cout << bank << ": time " << time << "," << value << endl;
    }
};

struct BuyQuote: public Quote
{
    BuyQuote(string _bk, int _ts=0, double _val=0):Quote(_bk, _ts, _val) {}
    static bool best_compare(BuyQuote q1, BuyQuote q2) {return q1.value > q2.value;}
};


struct SellQuote: public Quote
{
    SellQuote(string _bk, int _ts=0, double _val=0):Quote(_bk, _ts, _val) {}
    static bool best_compare(SellQuote q1, SellQuote q2) {return q1.value < q2.value;}
};


template <class T>
class HashHeap
{
  private:
    unordered_map<string, int> hsBank;
	vector<T> m_array;
  public:
	HashHeap() {}

    void print_all()
    {
        unordered_map<string, int>::iterator it = hsBank.begin();
        for(; it != hsBank.end(); it++)
        {
            cout << "Bank map :" << it->first << " <--> " << it->second << endl;
        }
    }

	T top() {return m_array[0];}
    void insert(T quote)
    {
        if(hsBank.find(quote.bank) != hsBank.end())
        {
            int pos = hsBank[quote.bank];
            T pre_quote = m_array[pos];

            //cout << "quote bank" << quote.bank << endl;
            //pre_quote.print();
            //quote.print();

            if(pre_quote.time > quote.time) return;
            m_array[pos] = quote;

            if(T::best_compare(quote, pre_quote))
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
            //cout << "Switch" << p << "<-->" << i << endl;
            swap(m_array[i], m_array[p]);
            hsBank[m_array[i].bank] = i;
            hsBank[m_array[p].bank] = p;
            heapify_down(p);
        }
    }
};






class Solution {
private:

    unordered_map<PAIR, HashHeap<BuyQuote> > mapPairBuy;
    unordered_map<PAIR, HashHeap<SellQuote> > mapPairSell;

public:
    void process(vector<string> quote)
    {
        int time_stamp = stoi(quote[0]);
        string pair = quote[1];
        string bank = quote[2];
        double buy_value = stod(quote[3]);
        double sell_value = stod(quote[4]);

        if(mapPairBuy.find(pair) == mapPairBuy.end())
            mapPairBuy[pair] =  HashHeap<BuyQuote>();
        if(mapPairSell.find(pair) == mapPairSell.end())
            mapPairSell[pair] = HashHeap<SellQuote>();

        HashHeap<BuyQuote> &buyHeap = mapPairBuy[pair];
        HashHeap<SellQuote> &sellHeap = mapPairSell[pair];

        buyHeap.insert(BuyQuote(bank, time_stamp, buy_value));
        sellHeap.insert(SellQuote(bank, time_stamp, sell_value));
        //buyHeap.print_all();
        //sellHeap.print_all();

        //cout << pair << ":" << time_stamp << ", " << bank << ", " << buy_value << ", " << sell_value << endl;
    }

    
    void Query(string pair)
    {
        HashHeap<BuyQuote> buyHeap = mapPairBuy[pair];
        HashHeap<SellQuote> sellHeap = mapPairSell[pair] ;
        
        BuyQuote bestBuyQuote = buyHeap.top();
        SellQuote bestSellQuote = sellHeap.top();
        cout << "Best " << pair << " Buy = "<< bestBuyQuote.value << " from " << bestBuyQuote.bank << endl;
        cout << "Best " << pair << " Sell = "<< bestSellQuote.value << " from " << bestSellQuote.bank << endl;  
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
            sol.Query("EURUSD");

        }
    }

    return 0;
}
