//
// Created by zhuhonglin on 2021/3/5.
//

#ifndef MYSTL_HASHTABLE_H
#define MYSTL_HASHTABLE_H

/// 开链法

// 先用 std 的 vector 代替
#include <vector>
#include "allocator.h"


namespace sstl {

    #define PRIME_NUM 99

    static constexpr size_t ht_prime_list[] ={
            101ull, 173ull, 263ull, 397ull, 599ull, 907ull, 1361ull, 2053ull, 3083ull,
            4637ull, 6959ull, 10453ull, 15683ull, 23531ull, 35311ull, 52967ull, 79451ull,
            119179ull, 178781ull, 268189ull, 402299ull, 603457ull, 905189ull, 1357787ull,
            2036687ull, 3055043ull, 4582577ull, 6873871ull, 10310819ull, 15466229ull,
            23199347ull, 34799021ull, 52198537ull, 78297827ull, 117446801ull, 176170229ull,
            264255353ull, 396383041ull, 594574583ull, 891861923ull, 1337792887ull,
            2006689337ull, 3010034021ull, 4515051137ull, 6772576709ull, 10158865069ull,
            15238297621ull, 22857446471ull, 34286169707ull, 51429254599ull, 77143881917ull,
            115715822899ull, 173573734363ull, 260360601547ull, 390540902329ull,
            585811353559ull, 878717030339ull, 1318075545511ull, 1977113318311ull,
            2965669977497ull, 4448504966249ull, 6672757449409ull, 10009136174239ull,
            15013704261371ull, 22520556392057ull, 33780834588157ull, 50671251882247ull,
            76006877823377ull, 114010316735089ull, 171015475102649ull, 256523212653977ull,
            384784818980971ull, 577177228471507ull, 865765842707309ull, 1298648764060979ull,
            1947973146091477ull, 2921959719137273ull, 4382939578705967ull, 6574409368058969ull,
            9861614052088471ull, 14792421078132871ull, 22188631617199337ull, 33282947425799017ull,
            49924421138698549ull, 74886631708047827ull, 112329947562071807ull, 168494921343107851ull,
            252742382014661767ull, 379113573021992729ull, 568670359532989111ull, 853005539299483657ull,
            1279508308949225477ull, 1919262463423838231ull, 2878893695135757317ull, 4318340542703636011ull,
            6477510814055453699ull, 9716266221083181299ull, 14574399331624771603ull, 18446744073709551557ull
    };

    // 找出最接近并大于等于 n 的那个质数
    inline size_t ht_next_prime(size_t n) {
        const size_t* first = ht_prime_list;
        const size_t* last = ht_prime_list + PRIME_NUM;
        const size_t* pos = std::lower_bound(first, last, n);
        return pos == last ? *(last-1) : *pos;
    }


    template <class T>
    class hashtable_node {
    public:
        hashtable_node<T>*  next_;
        T                   value_;

        hashtable_node() = default;
        hashtable_node(const T& n): next_(nullptr), value_(n) {}
        hashtable_node(hashtable_node&& node): next_(node.next_), value_(std::move(node.value_)) {
            node.next_ = nullptr;
        }
    };


    template <class T, class Hash, class KeyEqual>
    class hashtable {
    public:
        typedef hashtable_node<T>       node_type;
        typedef node_type*              node_ptr;
        typedef std::vector<node_ptr>   bucket_type;
        typedef size_t                  size_type;
        typedef Hash                    hasher;
        typedef KeyEqual                key_equal;
        typedef sstl::allocator<T>      data_allocator;
    private:
        bucket_type buckets_;
        size_type   bucket_size_;
        size_type   size_;
        float       mlf_;
        Hash        hash_;
        KeyEqual    equal_;

    public:
        // 构造、复制、移动、析构函数
        explicit hashtable(size_type bucket_count, const Hash& hash=Hash(), const KeyEqual& equal=KeyEqual())
            : size_(0), mlf_(1.0f), hash_(hash), equal_(equal) {
            init(bucket_count);
        }
        hashtable(const hashtable& rhs): hash_(rhs.hash_), equal_(rhs.equal_) {
            copy_init(rhs);
        }
        hashtable(hashtable&& rhs): bucket_size_(rhs.bucket_size_), size_(rhs.size_),
            mlf_(rhs.mlf_), hash_(rhs.hash_), equal_(rhs.equal_) {
            buckets_ = std::move(rhs.buckets_);
            rhs.bucket_size_ = 0;
            rhs.size_ = 0;
            rhs.mlf_ = 0.0f;
        }
        ~hashtable() {clear();}


        /*********helper function*********/
        void init(size_type n) {
            const auto bucket_nums = sstl::ht_next_prime(n);
            buckets_.reserve(bucket_nums);  // capacity = bucket_nums
            buckets_.assign(bucket_nums, nullptr);
            bucket_size_ = buckets_.size();
        }

        void copy_init(const hashtable& ht) {
            buckets_.reserve(ht.bucket_size_);
            buckets_.assign(ht.bucket_size_, nullptr);
            for (size_type i = 0; i < ht.bucket_size_; ++i) {
                node_ptr cur = ht.buckets_[i];
                if (cur) {
                    // 某 bucket 存在链表
                    node_ptr copy = create_node(cur->value_);
                    buckets_[i] = copy;
                    for (cur = cur->next_; cur ; cur = cur->next_){
                        copy->next_ = create_node(cur->value_);
                        copy = copy->next_;
                    }
                }
                bucket_size_ = ht.bucket_size_;
                mlf_ = ht.mlf_;
                size_ = ht.size_;
            }
        }

        node_ptr create_node(T value) {
            node_ptr tmp = new hashtable_node<T>(value);
            tmp->next_ = nullptr;
            return tmp;
        }

        void clear() {
            if (size_ != 0) {
                for (size_type i = 0; i < bucket_size_; ++i) {
                    node_ptr cur = buckets_[i];
                    while (cur != nullptr) {
                        node_ptr next = cur->next_;
                        destroy_node(cur);
                        cur = next;
                    }
                    buckets_[i] = nullptr;
                }
                size_ = 0;
            }
        }

        void destroy_node(node_ptr ptr) {
            data_allocator::destroy(&(ptr->value_));
            data_allocator::deallocate(ptr);
            ptr = nullptr;
        }

    };
}


#endif //MYSTL_HASHTABLE_H
