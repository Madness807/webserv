#ifndef MIMETYPEMANAGER_HPP
#define MIMETYPEMANAGER_HPP

#include <map>
#include <string>

class MimeTypeManager
{
    public:
        void initMimeTypes();
        std::string getMimeType(const std::string& extension) const;

    private:
        std::map<std::string, std::string> _mimeTypes;
};

#endif