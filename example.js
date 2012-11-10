var addon = require('./build/Release/varnishstat');

var mystuff = addon.fetchStats();

setInterval(function() {
  var counters = addon.fetchStats();
  Object.keys(counters)
        .filter(function (el) { return el.substring(0, 7) === 'backend' })
        .forEach(function (count) { console.log(count + ': ' + counters[count]); });
  console.log("---");
}, 1000);
