const char *indexHtml PROGMEM = R"(
<!doctype html>

<html>
    <head>
        <meta charset='utf-8' />
        <meta name='viewport' content='width=device-width, initial-scale=1' />

        <title>ESPway</title>

        <style>
            html {
                font-size: 32px;
            }

            body {
                font-family: sans-serif;
                text-align: center;
                margin: 0 auto;
            }

            button {
                font-size: 2rem;
                width: 4rem;
                height: 3rem;
            }
        </style>
    </head>

    <body>
        <h1>Led is <br /><span id='ledStatus'></span></h1>
        <button id='btnOn'>on</button>
        <button id='btnOff'>off</button>

        <script>
            (function() {
                'use strict'

                let byId = id => document.getElementById(id)

                function main() {
                    let ws = new WebSocket('ws://' + location.host + '/ws')
                    ws.binaryType = 'arraybuffer'

                    ws.addEventListener('message', e => {
                        let arr = new Uint8Array(e.data)
                        if (arr[0] == 1) {
                            byId('ledStatus').textContent = 'off'
                        } else {
                            byId('ledStatus').textContent = 'on'
                        }
                    })

                    let sendBytes = bytes => ws.send((new Uint8Array(bytes)).buffer)

                    byId('btnOn').addEventListener('click', () => sendBytes([0]))
                    byId('btnOff').addEventListener('click', () => sendBytes([1]))
                }

                window.addEventListener('load', main)
            })()
        </script>
    </body>
</html>

)";
