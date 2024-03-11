#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    //freopen("output.txt", "w", stdout);
    vector<pair<pair<double,double>,pair<double,double>>>data1;
    vector<pair<pair<double,double>,pair<double,double>>>data2;

    //Distance,Price and Rating query
    int distance, price;
    double rating;
    double preferred_max_price;
    double preferred_max_distance;
    double preferred_min_rating;
    cout << "Enter your preferred maximum distance: ";
    cin >> preferred_max_distance;
    cout << "Enter your preferred maximum price: ";
    cin >> preferred_max_price;
    cout << "Enter your preferred minimum rating: ";
    cin >> preferred_min_rating;
    double preferred_min_price=0;
    double preferred_min_distance=0;
    double preferred_max_rating=10;
//    cout << "Enter your preferred minimum distance: ";
//    cin >> preferred_min_distance;
//    cout << "Enter your preferred minimum price: ";
//    cin >> preferred_min_price;
//    cout << "Enter your preferred maximum rating: ";
//    cin >> preferred_max_rating;
    int id = 1000;
    freopen("input.txt", "r", stdin);
    //freopen("input2.txt", "r", stdin);
    map<int,int>mp;
    long double sum_x = 0;
    long double sum_y = 0;
    long double sum_z = 0;
    long double sum_x2 = 0;
    long double sum_xy = 0;
    long double sum_y2 = 0;
    long double sum_z2 = 0;
    long double sum_yz = 0;
    long double slope = 0,intersection = 0,n = 0;
    cout<<"After Linear Regression: "<<endl;
    cout<<"Distance:  "<<"Price:     "<<"Rating: "<<endl;
    while(cin >> distance >> price >> rating)
    {
        id++;
        if(distance==0&&price==0&&rating==0)
        {
            continue;
        }
        else if(distance!=0&&price!=0&&rating!=0)
        {
            sum_x+=distance;
            sum_y+=price;
            sum_z+=rating;
            sum_x2+=distance*distance;
            sum_y2+=price*price;
            sum_z2+=rating*rating;
            sum_xy+=distance*price;
            sum_yz+=price*rating;
            n++;
        }
        if(price==0)
        {
            slope = (n*sum_xy-sum_x*sum_y)/(n*sum_x2-sum_x*sum_x);
            intersection = (sum_y - slope*sum_x)/n;
            price = slope*distance+intersection;
            //cout<<"price "<<price<<endl;
        }
        if(distance==0)
        {
            slope = (n*sum_xy-sum_x*sum_y)/(n*sum_y2-sum_y*sum_y);
            intersection = (sum_x - slope*sum_y)/n;
            distance = slope*price+intersection;
            //cout<<"distance "<<distance<<endl;
        }
        if(rating==0)
        {
            slope = (n*sum_yz-sum_y*sum_z)/(n*sum_y2-sum_y*sum_y);
            intersection = (sum_z - slope*sum_y)/n;
            rating = slope*price+intersection;
            //cout<<"Rating "<<rating<<endl;

        }
        if(preferred_min_distance<=distance&&preferred_min_price<=price&&preferred_max_rating>=rating)
        {
            data1.push_back({{distance,price},{id,rating}});
        }
        if(preferred_min_distance<=distance&&preferred_min_price<=price&&preferred_max_rating>=rating)
        {
            data2.push_back({{price,rating},{id,distance}});
        }
        //cout<<distance<<"         "<<price<<"         "<<rating<<endl;

    }

    sort(data1.begin(),data1.end());
    auto itr = data1.begin();
    int point1  = itr->first.second;
    vector<pair<pair<double,double>,pair<double,double>>>ans1;
    vector<pair<pair<double,double>,pair<double,double>>>Final;
    ans1.push_back({{itr->first.first,itr->first.second},{itr->second.first,itr->second.second}});
    for(auto it = data1.begin(); it!=data1.end(); it++)
    {
        if(it->first.second<point1)
        {
            point1 = it->first.second;
            ans1.push_back({{it->first.first,it->first.second},{it->second.first,it->second.second}});
        }
    }
    cout<<endl;
    cout<<"Price and Distance Skyline point : "<<endl;
    cout<<endl;
    cout<<"Hotel ID:    "<<"Distance:       "<<"Price: "<<endl;
    for(auto it = ans1.begin(); it!=ans1.end(); it++)
    {

        cout<<it->second.first<<"          "<<it->first.first<<"            "<<it->first.second<<endl;
        if(mp.find(it->first.first)==mp.end())
        {
            Final.push_back({{it->first.first,it->first.second},{it->second.first,it->second.second}});
        }
        mp[it->first.first]++;

    }
    sort(data2.begin(),data2.end());
    auto itr2 = data2.begin();
    double point2  = itr2->first.second;
    vector<pair<pair<double,double>,pair<double,double>>>ans2;
    ans2.push_back({{itr2->first.first,itr2->first.second},{itr2->second.first,itr2->second.second}});
    set<double>st;
    st.insert(itr2->first.first);

    for(auto it = data2.begin(); it!=data2.end(); it++)
    {
        if(it->first.second>point2)
        {
            point2 = it->first.second;
            if(st.find(it->first.first)!=st.end())
            {
                ans2.pop_back();
            }
            ans2.push_back({{it->first.first,it->first.second},{it->second.first,it->second.second}});
            st.insert(it->first.first);

        }
    }
    cout<<endl;
    cout<<"Rating and Price Skyline point : "<<endl;
    cout<<endl;
    cout<<"Hotel ID:    "<<"Price:        "<<"Rating:  "<<endl;
    for(auto it = ans2.begin(); it!=ans2.end(); it++)
    {
        cout<<it->second.first<<"         "<<it->first.first<<"            "<<it->first.second<<endl;
        if(mp.find(it->second.second)==mp.end())
        {
            Final.push_back({{it->second.second,it->first.first},{it->second.first,it->first.second}});
        }
        mp[it->second.second]++;
    }
    sort(Final.begin(),Final.end());
    cout<<endl;
    cout<<"Final Skyline point : "<<endl;
    cout<<endl;
    cout<<"Hotel ID:    "<<"Distance:   "<<"Price:        "<<"Rating:  "<<endl;
    for(auto it = Final.begin(); it!=Final.end(); it++)
    {
        cout<<it->second.first<<"         "<<it->first.first<<"         "<<it->first.second<<"            "<<it->second.second<<endl;
    }


// Get user preferences

    vector<pair<pair<double, double>, pair<double, double>>> preferenceResult;

    for (auto it = Final.begin(); it != Final.end(); it++)
    {
        double distance = it->first.first;
        double price = it->first.second;
        double rating = it->second.second;

        // Check if the point satisfies user preferences
        if (distance <= preferred_max_distance &&
                price <= preferred_max_price &&
                rating >= preferred_min_rating)
        {
            preferenceResult.push_back({{it->second.first, distance}, {price, rating}});
        }
    }

    cout << endl;
    cout << "Preference Query Results: " << endl;
    cout<<endl;
    cout << "Hotel ID:    " << "Distance:   " << "Price:        " << "Rating:  " << endl;
    for (auto it = preferenceResult.begin(); it != preferenceResult.end(); it++)
    {
        cout << it->first.first << "         " << it->first.second << "         "
             << it->second.first << "            " << it->second.second << endl;
    }
    return 0;
}
