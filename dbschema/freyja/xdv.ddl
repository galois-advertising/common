{$
#include <iostream>
#include <vector>
$}

handlername = galois;
namespace=galois::freyja;

create datatable xdv_table {
    property {
        type = HashTable;
    };
    xdv_id : uint64_t;
    plan_id : uint32_t;
    unit_id : uint64_t;
    usr_id : uint32_t;
    word_id : uint64_t;
    bid : uint32_t;
    bid_word : array char[1024u];
    (xdv_id) : uint64key, primary_key;
};

create dataupdator xdv_view -> xdv_table {
    property {
        udf = xdv_view_to_xdv_table;
    };
};

