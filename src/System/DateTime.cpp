#include "DateTime.hpp"

DateTime::DateTime()
{
    timestamp = std::chrono::system_clock::now();
}

DateTime::DateTime(const TimeStamp& timestamp)
{
    this->timestamp = timestamp;
}

TimeStamp DateTime::Date()
{
    return timestamp;
}

int DateTime::Day()
{
    time_t tt = std::chrono::_V2::system_clock::to_time_t(timestamp);
    tm local_tm = *localtime(&tt);
    return local_tm.tm_mday;
}

int DateTime::DayOfWeek()
{
    time_t tt = std::chrono::_V2::system_clock::to_time_t(timestamp);
    tm local_tm = *localtime(&tt);
    return local_tm.tm_wday;
}

int DateTime::DayOfYear()
{
    time_t tt = std::chrono::_V2::system_clock::to_time_t(timestamp);
    tm local_tm = *localtime(&tt);
    return local_tm.tm_yday;
}

int DateTime::Hour()
{
    time_t tt = std::chrono::_V2::system_clock::to_time_t(timestamp);
    tm local_tm = *localtime(&tt);
    return local_tm.tm_hour;
}

int DateTime::Minute()
{
    time_t tt = std::chrono::_V2::system_clock::to_time_t(timestamp);
    tm local_tm = *localtime(&tt);
    return local_tm.tm_min;
}

int DateTime::Month()
{
    time_t tt = std::chrono::_V2::system_clock::to_time_t(timestamp);
    tm local_tm = *localtime(&tt);
    return local_tm.tm_mon;
}

void DateTime::AddMilliseconds(int64_t milliseconds)
{
    timestamp += std::chrono::milliseconds(milliseconds);
}

void DateTime::AddSeconds(int64_t seconds)
{
    timestamp += std::chrono::seconds(seconds);
}

void DateTime::AddMinutes(int64_t minutes)
{
    timestamp += std::chrono::minutes(minutes);
}

void DateTime::AddHours(int64_t hours)
{
    timestamp += std::chrono::hours(hours);
}

void DateTime::AddDays(int64_t days)
{
    timestamp += std::chrono::hours(days * 24);
}

DateTime DateTime::Now()
{
    return DateTime(std::chrono::system_clock::now());
}

int DateTime::Second()
{
    time_t tt = std::chrono::_V2::system_clock::to_time_t(timestamp);
    tm local_tm = *localtime(&tt);
    return local_tm.tm_sec;
}

int DateTime::Year()
{
    time_t tt = std::chrono::_V2::system_clock::to_time_t(timestamp);
    tm local_tm = *localtime(&tt);
    return local_tm.tm_year;
}

int64_t DateTime::TimeSinceEpochInSeconds()
{
    auto epoch = timestamp.time_since_epoch();
    auto value = std::chrono::duration_cast<std::chrono::seconds>(epoch);
    return value.count();        
}

int64_t DateTime::TimeSinceEpochInMilliseconds()
{
    auto epoch = timestamp.time_since_epoch();
    auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
    return value.count();        
}

std::string DateTime::FormattedTimestamp() const 
{
    auto now = std::chrono::system_clock::to_time_t(timestamp);
    std::tm tmNow = *std::localtime(&now);

    std::ostringstream oss;
    oss << std::put_time(&tmNow, "%m-%d-%Y %H:%M:%S");
    return oss.str();
}