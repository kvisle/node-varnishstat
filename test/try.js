var vows = require('vows')
  , assert = require('assert');

var varnishstat = require('../varnishstat');

vows.describe('fetchStats').addBatch({
  'returns': {
    topic: varnishstat.fetchStats(),

    'an object': function (stats) {
      assert.isObject(stats);
    },
    'with stats we know of': function (stats) {
      assert.isNumber(stats.backend_conn);
    }
  }
}).exportTo(module);
