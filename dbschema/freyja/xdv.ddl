{$
#include <iostream>
#include <vector>
#include "databus_event.pb.h"
$}

handlername = freyja_env;
namespace=galois::freyja;

create dataview xdv_view on gbus::xdv_event {
    property {
        udf = xdv_view_udf;
    };
    xdv_id : uint64_t;
    plan_id : uint32_t;
    unit_id : uint32_t;
    user_id : uint32_t;
    word_id : uint64_t;
    bid : uint32_t;
    bid_word : array char[1024u];
    derivative {
        bid_word_sign: uint64_t, from(bid_word);
    };
};

create datatable xdv_table {
    property {
        type = HashTable;
    };
    xdv_id : uint64_t;
    plan_id : uint32_t;
    unit_id : uint32_t;
    user_id : uint32_t;
    word_id : uint64_t;
    bid : uint32_t;
    bid_word : array char[1024u];
    (user_id, plan_id, unit_id, xdv_id) : uint64key, primary_key;
};

create dataupdator xdv_view -> xdv_table {
    property {
        udf = xdv_view_to_xdv_table;
    };
};

