#ifndef READER_H
#define READER_H

#include <optional>

#include "chartdata.h"

class IReader
{
public:
    virtual ~IReader() = default;

    virtual std::optional<ChartData> readFile(const QString& path) = 0;
};

class CSVReader : public IReader
{
public:
    std::optional<ChartData> readFile(const QString& path) override;
};

#endif // READER_H
