#!/bin/sh
test_main() {
    TARGET="$1"
    # Read test cases from file
    while IFS= read -r line; do
        ID=$(echo $line | cut -d'|' -f1)
        SW=$(echo $line | cut -d'|' -f2)
        EXPECTED_RESULT=$(echo $line | cut -d'|' -f3)
        if [ ! -z "$ID" ]; then
            rm ${RESULT_FILE}
            touch ${RESULT_FILE}
            # Run the compiled binary with the test case
            /bin/sh -c "${TARGET} \"${SW}\" > ${RESULT_FILE}"

            # Compare the result with the expected result
            RESULT=$(cat "${RESULT_FILE}")
            if [ "${RESULT}" = "${EXPECTED_RESULT}" ]; then
                echo "${ID} Test passed: Parent path correctly calculated."
            else
                echo "${ID} Test failed: Parent path calculation incorrect."
                echo "  .. Command : ${TARGET} ${SW} > ${RESULT_FILE}"
                echo "  .. Result  : ${RESULT}"
                echo "  .. Expected: ${EXPECTED_RESULT}"
                exit 1
            fi
        fi
    done < "$2"
    echo "All tests passed!"
}
test_main "$1" "$2"