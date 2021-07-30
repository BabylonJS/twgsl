// As described here: https://emscripten.org/docs/porting/connecting_cpp_and_javascript/Interacting-with-code.html#implement-a-c-api-in-javascript
mergeInto(LibraryManager.library, {
    return_string: function(data, length) {
        // Requires this handler function to be defined. Defining it is the responsibility
        // of whoever calls into the WASM.
        Module._return_string_callback(data, length);
    }
});