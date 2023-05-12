#pragma once

#include <nlohmann/json.hpp>
#include <tl/expected.hpp>

#include <system_error>
#include <format>

namespace lst::api
{
    template<typename T >
    using Result = tl::expected<T, std::error_code>;

    template<typename T >
    using PagedResult = Result< std::vector< T > >;

    struct HttpErrorCategory : public std::error_category
    {
        virtual const char * name() const noexcept
        {
            return "HttpError";
        }

        virtual std::string message( int error ) const
        {
            return std::format( "{}: {}", name(), error );
        };

        static std::error_code MakeError( int status )
        {
            static HttpErrorCategory s_category;
            return std::error_code{status, s_category};
        }

        static tl::unexpected< std::error_code > MakeUnexpected( int status )
        {
            return tl::make_unexpected( MakeError( status ) );
        }
    };
}