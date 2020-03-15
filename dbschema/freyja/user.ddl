{$
#include <iostream>
#include <vector>
#include "databus_event.pb.h"
$}

handlername = freyja_env;
namespace=galois::freyja;

create dataview user_view on gbus::user_event {
    property {
        udf = user_view_udf;
    };
    user_id : uint32_t;
    user_stat : uint32_t;
    region: uint64_t;
    user_name: array char[1024u];
    derivative {
        user_name_sign: uint64_t, from(user_name);
    };
};

create datatable user_table {
    property {
        type = HashTable;
    };
    user_id : uint32_t;
    user_stat : uint32_t;
    region: uint64_t;
    user_name_sign: uint64_t;
    (user_id) : uint32key, primary_key;
};

create dataupdator user_view -> user_table {
    property {
        udf = user_view_to_user_table;
    };
};

create indextable user_index on user_table::region {};

create indexupdator user_table -> user_index {};