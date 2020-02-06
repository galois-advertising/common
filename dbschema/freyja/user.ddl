{$
#include <iostream>
#include <vector>
$}

handlername = galois;
namespace=galois::freyja;

create dataview user_view on gbus::user_event {
    user_id : uint32_t;
    user_stat : uint32_t;
    region: uint64_t;
};

create datatable user_table {
    property {
        type = HashTable;
    };
    user_id : uint32_t;
    user_stat : uint32_t;
    region: uint64_t;
    (usr_id) : uint64key, primary_key;
};

create dataupdator user_view -> user_table {
    property {
        udf = user_view_to_user_table;
    };
};