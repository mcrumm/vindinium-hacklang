<?hh
namespace Hackdinium\Http;

use GuzzleHttp\Command\Guzzle\Description as BaseDescription;

class Description extends BaseDescription {
    public static function getServiceDescription() {
        return [
            'baseUrl' => 'http://vindinium.org/',
            'operations' => [
                'training' => [
                    'httpMethod' => 'POST',
                    'uri' => '/api/training',
                    'responseModel' => 'GameResponse',
                    'parameters' => [
                        'key' => [
                            'type' => 'string',
                            'location' => 'postField',
                            'required' => true,
                        ],
                        'turns' => [
                            'type' => 'integer',
                            'location' => 'postField',
                            'default' => 300,
                        ],
                        'map' => [
                            'type' => 'string',
                            'location' => 'postField',
                            'default' => null
                        ]
                    ]
                ],
                'move'  => [
                    'httpMethod'    => 'POST',
                    'uri'           => '/api/{url}',
                    'responseModel' => 'GameResponse',
                    'parameters'    => [
                        'url'   => [
                            'type'      => 'string',
                            'location'  => 'uri',
                            'required'  => true
                        ],
                        'dir'   => [
                            'type'      => 'string',
                            'location'  => 'postField',
                            'required'  => true
                        ]
                    ]
                ],
                'arena' => [
                    'httpMethod'    => 'POST',
                    'uri'           => '/api/arena',
                    'responseModel' => 'GameResponse',
                    'parameters'    => [
                        'key'   => [
                            'type'      => 'string',
                            'location'  => 'postField',
                            'required'  => true
                        ]
                    ]
                ]
            ],
            'models' => [
                'GameResponse' => [
                    'type' => 'object',
                    'additionalProperties' => [
                        'location' => 'json'
                    ]
                ],
            ]
        ];
    }

    public function __construct(array $options = []) {
        parent::__construct(static::getServiceDescription(), $options);
    }
}
