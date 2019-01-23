/*
 * Copyright (C) 2017 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

WI.ResourceDetailsSection = class ResourceDetailsSection
{
    constructor(title, className)
    {
        this._element = document.createElement("section");
        if (className)
            this._element.className = className;

        this._titleElement = this._element.appendChild(document.createElement("div"));
        this._titleElement.className = "title";
        this._titleElement.textContent = title;

        this._detailsElement = this._element.appendChild(document.createElement("div"));
        this._detailsElement.className = "details";

        // Ensures an empty line between sections when copying.
        this._element.appendChild(document.createElement("br"));
    }

    // Public

    get element() { return this._element; }
    get titleElement() { return this._titleElement; }
    get detailsElement() { return this._detailsElement; }

    toggleIncomplete(isIncomplete)
    {
        console.assert(typeof isIncomplete === "boolean");
        this.element.classList.toggle("incomplete", isIncomplete);
    }

    toggleError(isError)
    {
        console.assert(typeof isError === "boolean");
        this.element.classList.toggle("error", isError);
    }
};
