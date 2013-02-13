#include "stack-vector.hxx"

inline void test(const bool& pred) {
    if(!pred) throw std::runtime_error("Test failed.");
}

inline void fail() {
    throw std::runtime_error("Test failed.");
}

int main() {
    // construction: zero-capacity
    {
        andres::StackVector<int, 0> v;
        test(v.max_size() == 0);
        test(v.size() == 0);
    }

    // construction: empty
    {
        andres::StackVector<int, 1> v;
        test(v.max_size() == 1);
        test(v.size() == 0);
        test(v.empty());
    }

    // construction: non-empty
    {
        andres::StackVector<int, 10> v(5);
        test(v.max_size() == 10);
        test(v.size() == 5);
        test(!v.empty());
        for(size_t j=0; j<v.size(); ++j) {
            test(v[j] == 0);
        }
        test(v.data() == &v[0]);
    }

    // construction: non-empty with initialization
    {
        andres::StackVector<int, 10> v(5, 2);
        test(v.max_size() == 10);
        test(v.size() == 5);
        test(!v.empty());
        for(size_t j=0; j<v.size(); ++j) {
            test(v[j] == 2);
        }
    }

    // access
    {
        andres::StackVector<int, 10> v(5);
        for(size_t j=0; j<v.size(); ++j) {
            v[j] = static_cast<int>(j);
        }
        for(size_t j=0; j<v.size(); ++j) {
            test(v[j] == static_cast<int>(j));
            test(v.front() == 0);
            test(v.back() == 4);
        }
        const andres::StackVector<int, 10>& r = v;
        for(size_t j=0; j<v.size(); ++j) {
            test(r[j] == static_cast<int>(j));
        }
    }
    {
        andres::StackVector<int, 10> v(5);
        for(size_t j=0; j<v.size(); ++j) {
            v.at(j) = static_cast<int>(j);
        }
        for(size_t j=0; j<v.size(); ++j) {
            test(v.at(j) == static_cast<int>(j));
            test(v.front() == 0);
            test(v.back() == 4);
        }
        const andres::StackVector<int, 10>& r = v;
        for(size_t j=0; j<v.size(); ++j) {
            test(r.at(j) == static_cast<int>(j));
        }
        try {
            v.at(5); fail();
        }
        catch(std::out_of_range& e) {}
    }

    // resize
    {
        andres::StackVector<int, 10> v(5, 1);
        v.resize(10);
        assert(v.max_size() == 10);
        assert(v.size() == 10);
        for(size_t j=0; j<5; ++j) {
            test(v[j] == 1);
        }
        for(size_t j=5; j<v.size(); ++j) {
            test(v[j] == 0);
        }
    }
    {
        andres::StackVector<int, 10> v(5, 1);
        v.resize(10, 2);
        assert(v.max_size() == 10);
        assert(v.size() == 10);
        for(size_t j=0; j<5; ++j) {
            test(v[j] == 1);
        }
        for(size_t j=5; j<v.size(); ++j) {
            test(v[j] == 2);
        }
    }

    // push_back
    {
        andres::StackVector<int, 10> v(1, 2);
        v.push_back(3);
        test(v.size() == 2);
        test(v[0] == 2);
        test(v[1] == 3);
        v.push_back(4);
        test(v.size() == 3);
        test(v[0] == 2);
        test(v[1] == 3);
        test(v[2] == 4);
    }

    // iterators
    {
        typedef andres::StackVector<int, 10> StackVector;
        StackVector v(5);
        for(size_t j=0; j<v.size(); ++j) {
            v[j] = static_cast<int>(j);
        }
        test(std::distance(v.begin(), v.end()) == static_cast<std::ptrdiff_t>(v.size()));
        test(std::distance(v.rbegin(), v.rend()) == static_cast<std::ptrdiff_t>(v.size()));
        test(std::distance(v.cbegin(), v.cend()) == static_cast<std::ptrdiff_t>(v.size()));
        test(std::distance(v.crbegin(), v.crend()) == static_cast<std::ptrdiff_t>(v.size()));
        {
            StackVector::iterator it = v.begin();
            for(size_t j=0; j<v.size(); ++j, ++it) {
                test(*it == v[j]);
            }
            test(it == v.end());
        }
        {
            StackVector::const_iterator it = v.cbegin();
            for(size_t j=0; j<v.size(); ++j, ++it) {
                test(*it == v[j]);
            }
            test(it == v.cend());
        }
        {
            StackVector::reverse_iterator it = v.rbegin();
            for(size_t j=0; j<v.size(); ++j, ++it) {
                test(*it == v[v.size() - j - 1]);
            }
            test(it == v.rend());
        }
        {
            StackVector::const_reverse_iterator it = v.crbegin();
            for(size_t j=0; j<v.size(); ++j, ++it) {
                test(*it == v[v.size() - j - 1]);
            }
            test(it == v.crend());
        }
    }

    return 0;
}
