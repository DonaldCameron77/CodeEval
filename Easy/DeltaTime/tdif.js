// DELTA TIME - CodeEval Easy challenge
// CHALLENGE DESCRIPTION:
// 
// You are given the pairs of time values. The values are in the HH:MM:SS
// format with leading zeros. Your task is to find out the time difference
// between the pairs.
// 
// INPUT SAMPLE:
// 
// The first argument is a file that contains lines with the time pairs.
// 
// For example:
// 
// 14:01:57 12:47:11
// 13:09:42 22:16:15
// 08:08:06 08:38:28
// 23:35:07 02:49:59
// 14:31:45 14:46:56
// 
// OUTPUT SAMPLE:
// 
// Print to stdout the time difference for each pair, one per line. You
// must format the time values in HH:MM:SS with leading zeros.
// 
// For example:
// 
// 01:14:46
// 09:06:33
// 00:30:22
// 20:45:08
// 00:15:11

// chomp from http://3dmdesign.com/development/chomp-for-javascript
function chomp(raw_text) {
    return raw_text.replace(/(\n|\r)+$/, '');
}

// handle the problem that, for time represented as
// hh:mm:ss, we may have a field less than 19 and thus
// a leading zero must be added
function addLeadingZeroes(num)
{
    if (num < 10) {
        num = '0' + num.toString();
    }
    return num;
}

const hr = 0;
const min = 1;
const secs = 2; // apparently "sec" is reserved or something ... don't use!

function toNumeric(timeStringArr) {
    var ans = [];
    ans[hr]  = Number(timeStringArr[hr]);
    ans[min] = Number(timeStringArr[min]);
    ans[secs] = Number(timeStringArr[secs]);
    return ans;
}

function getSeconds(tyme)
{
    var totalSecs = ((tyme[hr] * 60) + tyme[min]) * 60 + tyme[secs];
    return totalSecs;
}

// per Steven Iseki's answer at 
// http://stackoverflow.com/questions/1322732/convert-seconds-to-hh-mm-ss-with-javascript
/** 
 * Convert seconds to hh-mm-ss format.
 * @param {number} totalSeconds - the total seconds to convert to hh-
 * mm-ss
**/
var SecondsTohhmmss = function(totalSeconds)
{
    var hours   = Math.floor(totalSeconds / 3600);
    var minutes = Math.floor((totalSeconds - (hours * 3600)) / 60);
    var seconds = totalSeconds - (hours * 3600) - (minutes * 60);

    // round seconds
    seconds = Math.round(seconds * 100) / 100

    var result = (hours < 10 ? "0" + hours : hours);
    result += ":" + (minutes < 10 ? "0" + minutes : minutes);
    result += ":" + (seconds  < 10 ? "0" + seconds : seconds);
    return result;
}

var fs  = require("fs");

// "main program"

fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line)
{
    line = chomp(line);
    if (line != "")
    {
        var times = line.split(" ");
        var time0 = times[0].split(":");
        var time1 = times[1].split(":");

        var sec0 = getSeconds( toNumeric( time0 ) );
        var sec1 = getSeconds( toNumeric( time1 ) );

        var tdif = Math.abs(sec0 - sec1);

        var answer = SecondsTohhmmss(tdif);
        console.log(answer);
    }
});

// eof

